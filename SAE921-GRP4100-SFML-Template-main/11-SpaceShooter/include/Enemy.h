#pragma once
#include <list>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "box2d/box2d.h"
#include "Asteroide.h"
#include "AsteroideManager.h"


class Game;

class Enemy
{
public:
	Enemy(b2World&, float, float, float);
	std::list<Asteroide> currentAsteroide;
	void Update();
	b2Timer timerBetweenAsteroide;
	float timeBetweenAsteroide = 500; //milliseconds
	b2Timer timerHealthBarShown;
	float timeHealthBarShown = 500;
	void HideHealthBar();
	sf::Texture enemyTexture;
	sf::Sprite enemySprite;
	b2Body* body = nullptr;
	float speed = 1.2f;

	void ShootAsteroide(b2World&);
	void FindAsteroidetoDestroy();
	void Move();
	float movementDirection;
	bool isTouched = false;	//More like isDead 
	bool canShoot = true;
	void SetupUpAndReadSFX(sf::SoundBuffer& neededBuffer);
	void DestroyIfOutOfBounds();
	b2Timer timerIndestructibleShoot;
	float timeBetweenIndestuctibleShoot = 1500;
	
	~Enemy();
	Enemy& operator=(const Enemy& other);
	int enemyHealth;
	sf::RectangleShape enemyHealthBar;
	sf::Vector2f currentHealthBarSize;
	void OnHit(); 
	b2Vec2 randomAsteroideSpawningPos;
	void RandomSpawn();
	float velocityAsteroideX;


private:
	b2World& _world;
	

};
