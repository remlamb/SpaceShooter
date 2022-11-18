#include <random>

#include "game.h"

#include <iostream>

#include "managers/textureManager.h"

Game::Game() :
	m_gravity(0.0f, 0.0f),
	m_world(m_gravity),
	m_ship(m_world),
	m_contacts(*this),
	m_missileManager(m_world),
	m_asteroidManager(m_world)
{
}

void Game::init() {

	TextureManager* texture_manager = TextureManager::Instance();

	m_window.create(sf::VideoMode(1280, 720), "Asteroid Spaceship");
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60.0f);

	m_ship.init(m_window.getSize());
	m_ship.move(sf::Vector2f(0.5f * m_window.getSize().x, 0.5f * m_window.getSize().y), sf::Vector2f(0, 0));

	m_gameOverTitle.setTexture(texture_manager->getGameOverTexture());
	m_gameOverTitle.setOrigin(0.5f * texture_manager->getGameOverTexture().getSize().x, 0.5f * texture_manager->getGameOverTexture().getSize().y);
	m_gameOverTitle.setPosition(0.5f * m_window.getSize().x, 0.5f * m_window.getSize().y);

	// Add a bouncer
// TOP LIMIT -------------------------------------------
	m_windowLimits.push_back(
		std::make_unique<Bouncer>(
			m_world,
			sf::Vector2f(0.5f * m_window.getSize().x, 0.0f),
			sf::Vector2f(m_window.getSize().x, 10.0f)
			)
	);
	// BOTTOM LIMIT -------------------------------------------
	m_windowLimits.push_back(
		std::make_unique<Bouncer>(
			m_world,
			sf::Vector2f(0.5f * m_window.getSize().x, m_window.getSize().y),
			sf::Vector2f(m_window.getSize().x, 10.0f)
			)
	);
	// LEFT LIMIT -------------------------------------------
	m_windowLimits.push_back(
		std::make_unique<Bouncer>(
			m_world,
			sf::Vector2f(0.0f, 0.5f * m_window.getSize().y),
			sf::Vector2f(10.0F, m_window.getSize().y)
			)
	);
	// RIGHT LIMIT -------------------------------------------
	m_windowLimits.push_back(
		std::make_unique<Bouncer>(
			m_world,
			sf::Vector2f(m_window.getSize().x, 0.5f * m_window.getSize().y),
			sf::Vector2f(10.0f, m_window.getSize().y)
			)
	);

	m_debugMode = false;

	// Register contacts
	m_world.SetContactListener(&m_contacts);

}

void Game::loop()
{
	while (m_window.isOpen())
	{
#pragma region Event processes
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			// Windows events -------------------------------------------------------------------------------
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
				return;
			}
			if (event.type == sf::Event::Resized)
			{
				auto view = m_window.getView();
				view.setSize(event.size.width, event.size.height);
				m_window.setView(view);
			}

			// Mouse events ---------------------------------------------------------------------------------
			if (event.type == sf::Event::MouseButtonReleased)
			{
			}

			// Keyboard event
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Key::D)
				{
					m_debugMode = !m_debugMode;
				}
				if (event.key.code == sf::Keyboard::Key::Space)
				{
					m_missileManager.AddMissile(m_ship);
					m_soundManager->playPiou();

				}
				if (event.key.code == sf::Keyboard::Key::Left || event.key.code == sf::Keyboard::Key::Right) {
					m_ship.setAngularDamping(10.0f);
				}

			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
			m_ship.speedUp(1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
			m_ship.speedDown(10.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			m_ship.rotateLeft(1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			m_ship.rotateRight(1.0f);
		}


#pragma endregion


#pragma region Physical process
		if (!m_gameOver)
			update();

#pragma endregion
		draw();

		m_soundManager->cleanSounds();

#pragma region Graphics process

#pragma endregion

	}
}

void Game::update()
{
	// Updating the world with a delay
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	m_world.Step(timeStep, velocityIterations, positionIterations);

	// Update the ship
	m_ship.update();

	// Update Life bars with the lif of the ship
	m_lifeBar.setLife(m_ship.getLife());
	m_lifeBar.update();
	if (m_ship.getLife() <= 0)
	{
		// LOOOOSSSEEEEERRRRRRRRRR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		m_gameOver = true;
		m_soundManager->playBoum();
		return;
	}

	// Udpate asteroids
	m_asteroidManager.update();
	m_missileManager.update();
	// Update limits
	for (auto& b : m_windowLimits) {
		b->update();
	}

	// Tick every 1.0sec
	sf::Time elapsed = clock.restart();
	collectedElapsed += elapsed;

	if (collectedElapsed.asSeconds() > 1.0f) {

		std::random_device rd; // obtain a random number from hardware
		std::mt19937 generator(rd()); // seed the generator
		std::uniform_int_distribution<> rndAngle(0, 360); // define the range
		std::uniform_int_distribution<> rndX(0, m_window.getSize().x); // define the range
		std::uniform_int_distribution<> rndY(0, m_window.getSize().y); // define the range

		sf::Vector2f rdnPos(rndX(generator), rndY(generator));

		// Pop an asteroid
		m_asteroidManager.AddAsteroid(sf::Vector2f(m_window.getSize()));

		collectedElapsed = sf::Time::Zero;

	}
}

void Game::draw()
{
	// Clear all background
	m_window.clear();

	// DRWA THINGS ----------------------------------------------------------
	// Draw the ship
	if (!m_gameOver)
		m_window.draw(m_ship);

	// Draw asteroids
	m_window.draw(m_asteroidManager);
	m_window.draw(m_missileManager);

	// Draw limits
	if (m_debugMode)
	{
		for (auto& b : m_windowLimits) {
			m_window.draw(*b);
		}
	}
	// Draw Life bar
	m_window.draw(m_lifeBar);

	if (m_gameOver)
		m_window.draw(m_gameOverTitle);

	// Display all elements
	m_window.display();
}

void Game::setDamagesToShip(float damages_)
{
	m_ship.setDamages(damages_);
	m_soundManager->playBoum();

}

void Game::putAsteroidToDeath(int idAsteroid_)
{
	m_asteroidManager.putAsteroidToDeath(idAsteroid_);
	std::cout << "Asteroid " << idAsteroid_ << " sent to death." << std::endl;
}
void Game::putMissileToDeath(int idMissile_)
{
	m_missileManager.putMissileToDeath(idMissile_);
	std::cout << "Missile " << idMissile_ << " sent to death." << std::endl;
}

