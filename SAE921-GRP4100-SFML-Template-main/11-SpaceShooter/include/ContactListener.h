#pragma once
#include "box2d/b2_world_callbacks.h"
#include "GameLimit.h"

class Game;

class ContactListener : public b2ContactListener
{
public:
	explicit ContactListener(Game& game);
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
private :
	Game& game_;
};