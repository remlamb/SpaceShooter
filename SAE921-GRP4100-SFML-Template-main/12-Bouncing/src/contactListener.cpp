#include "contactListener.h"

#include <iostream>
#include <box2d/b2_contact.h>

#include "ball.h";

void ContactListener::BeginContact(b2Contact* contact)
{
	std::cout << "Begin Contact" << std::endl;

	auto userDataA = contact->GetFixtureA()->GetUserData();
	auto userDataB = contact->GetFixtureB()->GetUserData();

	Ball* ball = reinterpret_cast<Ball*>(userDataA.pointer);
	if(ball != nullptr)
	{
		std::cout << "A is a Ball." << std::endl;
		ball->setNewColor();
		//ball->SetBrokenState();
	}

	ball = reinterpret_cast<Ball*>(userDataB.pointer);
	if(reinterpret_cast<Ball*>(userDataB.pointer) != nullptr)
	{
		std::cout << "B is a Ball." << std::endl;
		ball->setNewColor();
	}

}

void ContactListener::EndContact(b2Contact* contact)
{
	std::cout << "End Contact" << std::endl;
}