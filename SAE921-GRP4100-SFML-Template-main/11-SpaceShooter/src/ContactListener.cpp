#include "contactListener.h"
#include <iostream>
#include <box2d/b2_contact.h>
#include "Bullet.h"
#include "Asteroide.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"

ContactListener::ContactListener(Game& game) : game_(game)
{

}

void ContactListener::BeginContact(b2Contact* contact)
{
	auto userDataA = contact->GetFixtureA()->GetUserData().pointer;
	auto userDataB = contact->GetFixtureB()->GetUserData().pointer;

	if (userDataA != 0 && userDataB != 0) {
		auto infoA = reinterpret_cast<ContactEvent*>(userDataA);
		auto infoB = reinterpret_cast<ContactEvent*>(userDataB);

		//Asteroide et Bullet
		if (infoA->TypeOfContact == ContactType::Bullet) {
			if (infoB->TypeOfContact == ContactType::Asteroide) {
				infoA->Bullet->touchedSomething = true;
				if (infoB->Asteroide->isDestructible) {
					infoB->Asteroide->isTouched = true;
				}
			}
		}
		else if (infoB->TypeOfContact == ContactType::Bullet) {
			if (infoA->TypeOfContact == ContactType::Asteroide) {
				infoB->Bullet->touchedSomething = true;
				if (infoA->Asteroide->isDestructible) {
					infoA->Asteroide->isTouched = true;
				}
			}
		}

		
		//Asteroide et Player
		if (infoA->TypeOfContact == ContactType::Asteroide) {
			if (infoB->TypeOfContact == ContactType::Player) {
				infoA->Asteroide->isTouched = true;
				infoB->Player->OnHit();
			}
		}
		else if (infoB->TypeOfContact == ContactType::Asteroide) {
			if (infoA->TypeOfContact == ContactType::Player) {
				infoB->Asteroide->isTouched = true;
				infoA->Player->OnHit();
			}
		}


		//Asteroide et Game Bordure
		if (infoA->TypeOfContact == ContactType::GameLimit) {
			if (infoB->TypeOfContact == ContactType::Asteroide) {
				infoB->Asteroide->isTouched = true;
			}
		}
		else if (infoB->TypeOfContact == ContactType::GameLimit) {
			if (infoA->TypeOfContact == ContactType::Asteroide) {
				infoA->Asteroide->isTouched = true;
			}
		}

		//Bullet et Game Bordure
		if (infoA->TypeOfContact == ContactType::GameLimit) {
			if (infoB->TypeOfContact == ContactType::Bullet) {
				infoB->Bullet->touchedSomething = true;
			}
		}
		else if (infoB->TypeOfContact == ContactType::GameLimit) {
			if (infoA->TypeOfContact == ContactType::Bullet) {
				infoA->Bullet->touchedSomething = true;
			}
		}

		//Bullet et Enemy	//Scoring is changing here
		if (infoA->TypeOfContact == ContactType::Enemy) {
			if (infoB->TypeOfContact == ContactType::Bullet) {
				game_.score += 10;
				infoB->Bullet->touchedSomething = true;
				infoA->Enemy->OnHit();
				if (infoA->Enemy->enemyHealth <= 0) {
					game_.score += 40;
				}
			}
		}
		else if (infoB->TypeOfContact == ContactType::Enemy) {
			if (infoA->TypeOfContact == ContactType::Bullet) {
				game_.score += 10;
				infoA->Bullet->touchedSomething = true;
				infoB->Enemy->OnHit();
				if (infoB->Enemy->enemyHealth <= 0) {
					game_.score += 40;
				}
			}
		}
	}
}

void ContactListener::EndContact(b2Contact* contact)
{

}

