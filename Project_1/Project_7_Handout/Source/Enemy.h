#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(float x, float y);

	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* c1, Collider* c2);

public:
	// The current position in the world
	fPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;
	int countdown = 0;
	int random = rand() % 2;
	float cout = 0;
	bool vistard = false;

	bool candelete = false;
	bool dead = false;
	bool hitwallL = false;
	bool hitwallR = false;
	bool gravity = true;
	bool hit = false;
	bool once = true;
	bool push = false;
	bool rolling = false;
	bool InitialD = false;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;
	Animation snow;

	// The enemy's collider
	Collider* collider = nullptr;
	Collider* cfs = nullptr;
	Collider* balldash = nullptr;

	// Original spawn position. Stored for movement calculations
	fPoint spawnPos;
};

#endif // __ENEMY_H__