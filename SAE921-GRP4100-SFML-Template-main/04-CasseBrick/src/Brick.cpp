#include "Brick.h"

Brick::Brick(float posx, float posy) {
	brickShape.setSize(sf::Vector2f(80, 40));
	brickShape.setFillColor(sf::Color(219, 204, 118));
	brickShape.setOutlineThickness(-6);
	brickShape.setOutlineColor(sf::Color(102, 84, 64));
	brickShape.setPosition(posx, posy);
}

void Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(brickShape, states);
}
