#pragma once
#include <iostream>
#include <box2d/b2_settings.h>
#include "Asteroide.h"

class Asteroide;
class Bullet;
class Player;
class GameLimit;
class Enemy;

// Event Type -------------------------------------------
enum class ContactType
{
	Bullet, Asteroide, Player, GameLimit, Enemy, None
};

class ContactEvent
{
public:
	ContactType TypeOfContact = ContactType::None;

	ContactEvent(Bullet& bullet) : TypeOfContact(ContactType::Bullet), Bullet(&bullet) { };
	Bullet* Bullet = nullptr;

	ContactEvent(Asteroide& asteroide) : TypeOfContact(ContactType::Asteroide), Asteroide(&asteroide) { };
	Asteroide* Asteroide = nullptr;
	
	ContactEvent(Player& player) : TypeOfContact(ContactType::Player), Player(&player) { };
	Player* Player = nullptr;

	ContactEvent(GameLimit& gamelimit) : TypeOfContact(ContactType::GameLimit), GameLimit(&gamelimit) { };
	GameLimit* GameLimit = nullptr;

	ContactEvent(Enemy& enemy) : TypeOfContact(ContactType::Enemy), Enemy(&enemy) { };
	Enemy* Enemy = nullptr;

private:

};
