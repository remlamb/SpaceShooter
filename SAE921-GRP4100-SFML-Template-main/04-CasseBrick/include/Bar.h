#pragma once 
#include <iostream>
#include "SFML/Graphics.hpp"


class Bar : public sf::Drawable, public sf::Transformable
{
public:
	Bar();

	sf::RectangleShape mainBar;

	void draw(sf::RenderTarget&, sf::RenderStates) const override; //Override of the draw function from Drawable
	void MoveRight();	//change Bar position, called when player use the move input 
	void MoveLeft();	//change Bar position, called when player use the move input 

private:

};