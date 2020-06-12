#ifndef __ENEMY_MINIBOSS_H__
#define __ENEMY_MINIBOSS_H__

#include "Enemy.h"
#include "p2Point.h"

class MiniBoss : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	MiniBoss(float x, float y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	Animation walkLAnim;
	Animation walkRAnim;
	Animation downRAnim;
	Animation downLAnim;
	Animation Ldead;
	Animation Rdead;
	Animation nothing;
};

#endif // __ENEMY_RedDemon_H__