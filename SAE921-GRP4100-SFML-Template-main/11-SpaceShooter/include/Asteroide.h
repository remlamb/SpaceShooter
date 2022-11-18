#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "ContactEvent.h"

class Asteroide : public sf::Drawable, public sf::Transformable
{
public:
	sf::CircleShape asteroideShape;
	float speed = 2.2;
	float velocityAsteroideX;
	b2Body* body = nullptr;
	bool isTouched = false;
	bool isDestructible = true;

	Asteroide(b2World& world, float posX, float posY, bool, float);
	void Update();
	void draw(sf::RenderTarget&, sf::RenderStates) const override; //Override of the draw function from Drawable
	~Asteroide();

	Asteroide& operator=(const Asteroide& other);

private:
	b2World& _world;

};