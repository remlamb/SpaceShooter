#include "Bar.h"

Bar::Bar() {
	mainBar.setSize(sf::Vector2f(100, 10));
	mainBar.setFillColor(sf::Color(222, 222, 222));
	mainBar.setOutlineThickness(-4);
	mainBar.setOutlineColor(sf::Color(38, 38, 38));
	mainBar.setOrigin(mainBar.getSize().x/2, mainBar.getSize().y/2);
	mainBar.setPosition(300, 520);
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(mainBar, states);
}

void Bar::MoveRight() {
	auto position = getPosition();
	position.x += 20;
	setPosition(position);
}

void Bar::MoveLeft() {
	auto position = getPosition();
	position.x -= 20;
	setPosition(position);
}