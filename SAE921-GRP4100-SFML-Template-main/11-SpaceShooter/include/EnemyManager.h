#pragma once
#include <list>
#include "Enemy.h"
#include "box2d/b2_timer.h"
#include "AsteroideManager.h"

class EnemyManager
{
public:
	EnemyManager();
	std::list<Enemy> currentEnemy;
	b2Timer timerBetweenEnemy;
	float timeBetweenEnemy = 1200; //milliseconds
	int spawnIntPos;

	void AddEnemy(b2World&);
	void FindEnemytoDestroy();
	void PlayDestroySound();
	void Render(sf::RenderWindow& window);

	sf::SoundBuffer sfxEnemyDeath;
	sf::Sound sound;

private:

};