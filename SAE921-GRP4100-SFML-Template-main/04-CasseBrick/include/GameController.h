#pragma once 
#include <vector>
#include "Brick.h"
#include"Bar.h"
#include"Ball.h"

class GameController
{
public:
	GameController();

	std::vector<Brick> bricks;
	Bar bar;
	Ball ball;

	void SetupBricks(); //create a set of bricks
	void Init();	//fonction that set up the SFML window, main music and spawn brick. Then launch the update fonction. 
	void Update(sf::RenderWindow&);	//Part of the code that turn when the window is open. 


private:

};
