#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window//Event.hpp"
#include "box2d/b2_world.h"
#include "box2d/b2_math.h"

#include "ball.h"
#include "bouncer.h"
#include "contactListener.h"

using namespace std;

class Game{
public:
	Game();
	void init();
	void loop();

	b2World& getWorld() { return _world; };

	static b2Vec2 pixelsToMeters(sf::Vector2f pixels);
	static b2Vec2 pixelsToMeters(sf::Vector2u pixels);
	static float pixelsToMeters(float pixels);
	static sf::Vector2f metersToPixels(b2Vec2 meters);

	static const float pixelsMetersRatio;

private:

	// The window ---------------------------------------------
	sf::RenderWindow window_;

	// The physical world -------------------------------------
	b2Vec2 gravity_;
	b2World _world;

	Ball theBall;
	Bouncer theBouncer;

	ContactListener _contactListener;

};
