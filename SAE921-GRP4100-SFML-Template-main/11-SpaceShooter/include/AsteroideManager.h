#pragma once
#include <list>
#include "Asteroide.h"
#include "box2d/b2_timer.h"
#include "Enemy.h"
#include "EnemyManager.h"

class AsteroideManager
{
public:
	AsteroideManager();
	std::list<Asteroide> currentAsteroide;
	void FindAsteroidetoDestroy();

private:

};
