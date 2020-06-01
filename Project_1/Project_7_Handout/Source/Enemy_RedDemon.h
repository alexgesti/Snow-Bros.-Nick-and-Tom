#ifndef __ENEMY_REDDEMON_H__
#define __ENEMY_REDDEMON_H__

#include "Enemy.h"
#include "p2Point.h"

class Enemy_RedDemon : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_RedDemon(float x, float y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation walkRAnim;
	Animation walkLAnim;
	Animation downRAnim;
	Animation downLAnim;
	Animation turnRAnim;
	Animation turnLAnim;
	Animation Ldead;
	Animation Rdead;
	Animation nothing;
};

#endif // __ENEMY_RedDemon_H__