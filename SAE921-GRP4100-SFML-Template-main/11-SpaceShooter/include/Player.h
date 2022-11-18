#pragma once
#include <iostream>
#include <list>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "box2d/box2d.h"
#include "Bullet.h"
#include "ContactEvent.h"
#include "HealthBar.h"


class Game;

class Player
{
public:
	Player(b2World& world, sf::RenderWindow& window);
	int playerHealth;

	float pixelsMetersRatio = 100.0f;

	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::SoundBuffer sfxShooting;
	sf::SoundBuffer sfxOnHit;
	sf::Sound sound;
	sf::Sound onHitSound;
	b2Body* body = nullptr;
	float speed = 6.0f;

	std::list<Bullet> currentBullet;


	void Init();
	void Update();
	void Render();


	void Move(float, float);
	void Shooting(b2World& world);
	void OnHit();

	void EraseBulletIfTouch();

	void SetupUpAndReadSFX(sf::SoundBuffer& neededBuffer);

	bool isShooting = false;
	bool canShoot = true;

	bool IsOutOfBounds();

	b2Timer timerBetweenBullet;
	float timeBetweenBullet = 100; //milliseconds

	HealthBar healthbar;

private:
	b2World& _world;
	sf::RenderWindow& _window;
};