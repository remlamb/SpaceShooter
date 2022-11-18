#include "HealthBar.h"

HealthBar::HealthBar() {

	currentHealthBarSize = sf::Vector2f(100, 10);
	healthBordure.setSize(currentHealthBarSize);
	healthBordure.setFillColor(sf::Color(0, 0, 0, 0));
	healthBordure.setOutlineThickness(5);
	healthBordure.setOutlineColor(sf::Color(33, 33, 33));

	healthBar.setSize(sf::Vector2f(100, 10));
	healthBar.setFillColor(sf::Color(255, 82, 69));

	setPosition(25, 25);
}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(healthBar, states);
	target.draw(healthBordure, states);
}