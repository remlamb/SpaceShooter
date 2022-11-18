#pragma once 
#include <iostream>
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "ContactEvent.h"


class Bullet
{
public:
	Bullet(float, float, b2World& world);
	sf::Texture laserTexture;
	sf::Sprite laserSprite;
	b2Body* body = nullptr;
	bool touchedSomething = false;

	void Update();
	~Bullet();
	Bullet& operator=(const Bullet& other);

private:
	b2World& _world;

};
