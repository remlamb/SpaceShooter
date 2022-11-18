#pragma once 
#include "box2d/box2d.h"
#include "ContactEvent.h"


class GameLimit
{
public:
	GameLimit();
	b2Body* body = nullptr;
	void SetUpBordure(b2World&, sf::RenderWindow&); //create invisible wall around the window, use to destroy projectile
	void SetUpABordure(int, int, int, int, b2World&);

private:

};