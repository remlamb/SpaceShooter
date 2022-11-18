#pragma once
#include <iostream>
#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Bar.h"

#include "Brick.h"

class Ball : public sf::Drawable, public sf::Transformable
{
public:
	Ball();

	sf::Vector2i direction;
	int speed = 8;
	sf::CircleShape ballShape;
	bool isLaunched;
	sf::SoundBuffer sfxBrick;
	sf::SoundBuffer sfxBordure;
	sf::SoundBuffer sfxUnBordure;
	sf::Sound sound;

	void Launch();	//set the bool isLaunched to true, and give a direction,
	void Move();	//Make the ball move when she s launched, movement is impact by speed and direction
	void Bounce(int, int);	//get a number for x and y axis, switch the direction to the given number

	void SetupUpAndReadSFX(sf::SoundBuffer&);	//input a sound buffer and play it 

	void BallOutofRange();	//Change direction if ball is on the side of the window, then play a sound
	void IsCollidingBar(Bar);	//create a hitbox based on the given Bar, Bounce the ball if she touched the created hitbox and play a sound.
	bool IsCollidingBrick(Brick&);	//create a hitbox based on the given Brick, Bounce the ball if she touched the created hitbox and play a sound.

	void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:

};