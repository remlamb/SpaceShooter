#pragma once 
#include "box2d/b2_world.h"
#include "box2d/box2d.h"
#include "ContactEvent.h"
#include <iostream>
#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "box2d/b2_timer.h"
#include "HealthBar.h"
#include "Player.h"
#include "EnemyManager.h"
#include "ContactListener.h"


class Game
{
public:
	Game();

	void Init();
	void Update();


	void InitScore();
	void UpdateScore();
	void RenderScore();

	void SetPause();

	//Limit de jeu
	b2Body* body = nullptr;
	int score;
	bool isPaused;
	
	Player player;
	EnemyManager enemyManager;
	GameLimit gl;
	ContactListener _contactListener;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Font font;
	sf::Text scoreText;

	b2World& getWorld() { return _world; };

	//Death Screen
	sf::RectangleShape deathBackground;
	sf::Text deathText;
	sf::Text finalScore;
	void InitDeathScreen();
	void OnPlayerDeath();
	void RenderDeathScreen();

	void EscapeScreen(); //if player out of bounds pause + show an alternative end message   //Use the death screen to be render

	void SetSpawnTimefaster();	//for enemy spawn //change enemyManager float 
	b2Timer timerBoost;
	float timeBetweenBoost = 10000;

	sf::SoundBuffer sfxAmbiantSound;
	sf::SoundBuffer sfxEndSound;
	sf::Sound sound;
	bool isEndSoundSet;	//use in order to load the death sound one time when player is dead

	void MainMenu();
	void RenderMainMenu();
	sf::RectangleShape launchMenuBackground;
	sf::Text launchText;
	sf::Text launchTextBtn;
	sf::Text infoText;
	bool isMainMenuLaunch;
	float timeStep;
	bool onStart;

	void GameUpdate(); //Update when game is not paused
	void GamePaused();	//Set up everything to paused the game //stop spawn 
	void GameRender(); //Everything the game had to render

	void JoystickInput();
	void EventAndKeyboardInput();


private:
	sf::RenderWindow _window;
	b2World _world;
	b2Vec2 _gravity;
};
