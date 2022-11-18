#pragma once
#include "SFML/Graphics.hpp"

class Brick : public sf::Drawable, public sf::Transformable
{
public:
	Brick(float, float); //Need a X and a Y position to be created
	sf::RectangleShape brickShape;
	void draw(sf::RenderTarget&, sf::RenderStates) const override; //Override of the draw function from Drawable

};