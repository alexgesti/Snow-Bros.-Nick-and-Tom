#ifndef __ENEMY_RedDemon_H__
#define __ENEMY_RedDemon_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_RedDemon : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_RedDemon(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	float timerw = 0;
	int twalk = 0;
	int speed = 1;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation walkRAnim;
	Animation walkLAnim;
	Animation downRAnim;
	Animation downLAnim;
	Animation turnRAnim;
	Animation turnLAnim;
};

#endif // __ENEMY_RedDemon_H__