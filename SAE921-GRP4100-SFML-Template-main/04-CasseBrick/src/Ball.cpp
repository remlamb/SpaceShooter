#include "Ball.h"

Ball::Ball()
{
	isLaunched = false;

	ballShape.setRadius(4);
	ballShape.setFillColor(sf::Color::White);
	ballShape.setOrigin(ballShape.getRadius(), ballShape.getRadius());
	setPosition(300, 500);

	if (!sfxBrick.loadFromFile("data/Pok.ogg")) {
		std::cout << "SoundEffect failed to load" << std::endl;
	}
	if (!sfxBordure.loadFromFile("data/TouchedBordure.ogg")) {
		std::cout << "SoundEffect failed to load" << std::endl;
	}
	if (!sfxUnBordure.loadFromFile("data/TouchedUnauthorizedBordure.ogg")) {
		std::cout << "SoundEffect failed to load" << std::endl;
	}
}

void Ball::Launch() {

	isLaunched = true;
	direction = sf::Vector2i(-1, -1);

}

void Ball::Move() {
	if (isLaunched) {
		auto position = getPosition();
		position.x += direction.x * speed;
		position.y += direction.y * speed;
		setPosition(position);
	}
}

void Ball::Bounce(int x, int y) {
	direction = sf::Vector2i(direction.x * x, direction.y * y);
}

void Ball::SetupUpAndReadSFX(sf::SoundBuffer& neededBuffer) {
	sound.setBuffer(neededBuffer);
	sound.play();
}

void Ball::BallOutofRange() {
	auto position = getPosition();
	if (position.y <= 0) {
		SetupUpAndReadSFX(sfxBordure);
		Bounce(1, -1);
		return;
	}
	if (position.y >= 600) {
		SetupUpAndReadSFX(sfxUnBordure);
		Bounce(1, -1);
		return;
	}

	if (position.x <= 0) {
		SetupUpAndReadSFX(sfxBordure);
		Bounce(-1, 1);
		return;
	}
	if (position.x >= 600) {
		SetupUpAndReadSFX(sfxBordure);
		Bounce(-1, 1);
		return;
	}
}

void Ball::IsCollidingBar(Bar otherRect) {
	// Define a rectangle  //this rectangle is the hitbox of the bar
	sf::IntRect interBar(otherRect.getPosition().x + 300 - (otherRect.mainBar.getSize().x/2), otherRect.mainBar.getPosition().y - 10, otherRect.mainBar.getSize().x, otherRect.mainBar.getSize().y * 2); //Some mathematics to put the hitbox at the good place because of the Bar got a different origin position //y-10 and size *2 for a better sensation of bar hitting the ball and not enter in it (hitbox oversized so it can contains when the ball seems to be on the bar)
	bool intersectBetweenBallAndBar = interBar.contains(getPosition().x, getPosition().y);

	if (isLaunched) {
		if (intersectBetweenBallAndBar) {
			SetupUpAndReadSFX(sfxBrick);
			Bounce(1, -1);
		}
	}
}

bool Ball::IsCollidingBrick(Brick& brick) {
	// Define a rectangle  //this rectangle is the hitbox of the brick
	sf::IntRect interBar(brick.brickShape.getPosition().x, brick.brickShape.getPosition().y, brick.brickShape.getSize().x, brick.brickShape.getSize().y);
	bool intersectBetweenBallAndBar = interBar.contains(getPosition().x, getPosition().y);

	if (intersectBetweenBallAndBar) {
		SetupUpAndReadSFX(sfxBrick);
		Bounce(1, -1);
		return true;
	}
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(ballShape, states);
}

