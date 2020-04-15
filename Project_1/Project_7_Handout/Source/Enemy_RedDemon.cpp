#include "Enemy_RedDemon.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_RedDemon::Enemy_RedDemon(int x, int y) : Enemy(x, y)
{
	

	walkRAnim.PushBack({ 139, 1, 29, 28 });
	walkRAnim.PushBack({ 170, 1, 30, 28 });
	walkRAnim.PushBack({ 203, 2, 29, 27 });
	walkRAnim.speed = 0.1f;

	walkLAnim.PushBack({ 103, 1, 29, 28 });
	walkLAnim.PushBack({ 71, 1, 30, 28 });
	walkLAnim.PushBack({ 39, 2, 29, 27 });
	walkLAnim.speed = 0.1f;

	downRAnim.PushBack({ 139, 68, 27, 25 });
	downRAnim.PushBack({ 172, 64, 26 ,32 });
	downRAnim.speed = 0.1f;

	downLAnim.PushBack({ 104, 68, 27 , 25 });
	downLAnim.PushBack({ 72, 64, 26 , 32 });
	downLAnim.speed = 0.1f;

	turnRAnim.PushBack({ 236, 2, 27, 27 });
	turnRAnim.speed = 0.1f;

	turnLAnim.PushBack({ 8, 2, 27 , 27 });
	turnLAnim.speed = 0.1f;
	// TODO 3: Have the Brown Cookies describe a path in the screen
	
	currentAnim = &walkRAnim;

	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedDemon::Update()
{
	//path.Update();
	path.PushBack({ 1.0f, 0.0f }, twalk, &walkRAnim);
	path.PushBack({ -1.0f, 0.0f }, twalk, &walkLAnim);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
