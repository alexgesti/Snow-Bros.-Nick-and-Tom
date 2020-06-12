#ifndef __ENEMY_BOSS_H__
#define __ENEMY_BOSS_H__

#include "Enemy.h"
#include "p2Point.h"

class Enemy_Boss : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Boss(float x, float y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	int jumpbt = (rand() % 4 + 11) * 100;
	bool dead = false;
	bool cambio = false;

private:
	Animation iddle;
	Animation deadboss;
	Animation jumpboss;
};

#endif // __ENEMY_RedDemon_H__