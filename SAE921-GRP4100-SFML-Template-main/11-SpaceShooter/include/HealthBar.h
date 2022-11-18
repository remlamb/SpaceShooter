#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class HealthBar : public sf::Drawable, public sf::Transformable
{
public:
	HealthBar();
	sf::RectangleShape healthBar;
	sf::RectangleShape healthBordure;
	sf::Vector2f currentHealthBarSize;
	void draw(sf::RenderTarget&, sf::RenderStates) const override; //Override of the draw function from Drawable

private:

};
