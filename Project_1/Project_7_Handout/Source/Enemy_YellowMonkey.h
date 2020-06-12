#ifndef __ENEMY_YELLOWMONKEY_H__
#define __ENEMY_YELLOWMONKEY_H__

#include "Enemy.h"
#include "p2Point.h"

class Enemy_YellowMonkey : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_YellowMonkey(float x, float y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	int jumpt = (rand() % 4 + 1) * 100;

private:
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation walkLAnim;
	Animation walkRAnim;
	Animation downRAnim;
	Animation downLAnim;
	Animation Ldead;
	Animation Rdead;
	Animation JumpL;
	Animation JumpR;
	Animation nothing;
};

#endif // __ENEMY_RedDemon_H__
