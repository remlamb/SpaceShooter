#include "Player.h"
#include "Game.h"
#include "SFMLToBox2D.h"

Player::Player(b2World& world, sf::RenderWindow& window) : _world(world), _window(window) {
    playerHealth = 10;

    if (!sfxShooting.loadFromFile("data/Sound/PlayerFire.ogg")) {
        std::cout << "SoundEffect failed to load" << std::endl;
    }

    if (!sfxOnHit.loadFromFile("data/Sound/OnHit.ogg")) {
        std::cout << "SoundEffect failed to load" << std::endl;
    }
}

void Player::Init() {
    playerHealth = 10;
    healthbar.currentHealthBarSize = sf::Vector2f(100, 10);

    playerTexture.loadFromFile("data/Ship.png");
    playerSprite.setTexture(playerTexture);
    playerSprite.setOrigin(playerTexture.getSize().x / 2.0f, playerTexture.getSize().y / 2.0f);

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(PixelsToMeters(_window.getSize().x/2), PixelsToMeters(-500));
    body = _world.CreateBody(&bodyDef);

    // Shape of the physical
    b2PolygonShape playerBox;
    playerBox.SetAsBox(PixelsToMeters(playerTexture.getSize().x *0.5), PixelsToMeters(playerTexture.getSize().y *0.5));

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &playerBox;
    playerFixtureDef.density = 0.0f;
    playerFixtureDef.friction = 1.0f;

    ContactEvent* m_userData = new ContactEvent(*this);
    playerFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);

    body->CreateFixture(&playerFixtureDef);
}

void Player::Update() {
    b2Vec2 position = body->GetPosition();
    sf::Vector2f graphicPosition = MetersToPixels(position);
    playerSprite.setPosition(graphicPosition);

    EraseBulletIfTouch();
    for (auto& bullet : currentBullet) {
        bullet.Update();
    }  
}

void Player::Render() {
    _window.draw(playerSprite);
    _window.draw(healthbar);

    for (auto& bullet : currentBullet) {
        _window.draw(bullet.laserSprite);
    }

}

void Player::Move(float directionX, float directionY) {
    body->SetLinearVelocity(b2Vec2(directionX * speed, directionY * speed));
    b2Vec2 position = body->GetPosition();
    sf::Vector2f graphicPosition = MetersToPixels(position); // sf::Vector2f(position.x, -1 * position.y);
    playerSprite.setPosition(graphicPosition);        // Set the position of the Graphic object
    
}

void Player::Shooting(b2World& world) {
    if (canShoot) {
        if (timerBetweenBullet.GetMilliseconds() > timeBetweenBullet) {
            SetupUpAndReadSFX(sfxShooting);
            currentBullet.emplace_back(body->GetPosition().x * 100, body->GetPosition().y * 100 + 50, world);
            timerBetweenBullet.Reset();
        }
    }
}

void Player::OnHit() {
    playerHealth -= 2;
    healthbar.currentHealthBarSize -= sf::Vector2f(20, 0);
    if (healthbar.currentHealthBarSize.x <= 0) {
        healthbar.currentHealthBarSize.x = 0;
    }
    healthbar.healthBar.setSize(healthbar.currentHealthBarSize);
    onHitSound.setBuffer(sfxOnHit);
    onHitSound.play();
}

void Player::EraseBulletIfTouch() {
    std::erase_if(currentBullet, [](Bullet& a) {return a.touchedSomething; });
}

void Player::SetupUpAndReadSFX(sf::SoundBuffer& neededBuffer) {
    sound.setBuffer(neededBuffer);
    sound.play();
}

bool Player::IsOutOfBounds() {
    b2Vec2 position = body->GetPosition();
    sf::Vector2f graphicPosition = MetersToPixels(position);

    if (graphicPosition.x < -400 || graphicPosition.x > _window.getSize().x + 400 || graphicPosition.y > _window.getSize().y + 400 || graphicPosition.y < -400) {
        return true;
    }
    else {
        return false;
    }
}
