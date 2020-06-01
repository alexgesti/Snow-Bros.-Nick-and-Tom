#include "Enemy_RedDemon.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_RedDemon::Enemy_RedDemon(int x, int y) : Enemy(x, y)
{
	walkRAnim.PushBack({ 147, 6, 29, 28 });
	walkRAnim.PushBack({ 178, 6, 30, 28 });
	walkRAnim.PushBack({ 211, 7, 29, 27 });
	walkRAnim.speed = 0.1f;

	walkLAnim.PushBack({ 111, 6, 29, 28 });
	walkLAnim.PushBack({ 79, 6, 30, 28 });
	walkLAnim.PushBack({ 47, 7, 29, 27 });
	walkLAnim.speed = 0.1f;

	downRAnim.PushBack({ 180, 69, 26 ,32 });

	downLAnim.PushBack({ 80, 69, 26 , 32 });

	turnRAnim.PushBack({ 236, 2, 27, 27 });

	turnLAnim.PushBack({ 8, 2, 27 , 27 });

	Ldead.PushBack({ 15, 41, 28, 26 });
	Ldead.PushBack({ 47, 39, 28, 30 });
	Ldead.speed = 0.1f;

	Rdead.PushBack({ 179, 40, 28, 26 });
	Rdead.PushBack({ 147, 38, 28, 30 });
	Rdead.speed = 0.1f;

	if (random == 0) {
		vistard = true;
	}
	else if (random == 1) {
		vistard = false;
	}

	collidersnow = App->collisions->AddCollider({ 0, 0, 24, 27 }, Collider::Type::SNOWBALL, (Module*)App->enemies);
}

void Enemy_RedDemon::Update()
{
	random--;
	if (random <= 0) {
		if (vistard == false) {
			vistard = true;
		}
		else if (vistard == true) {
			vistard = false;
		}
		random = (rand() % 4 + 1) * 100;
	}

	if (gravity == true) {
		position.y += 1;
		if (vistard == true) {
			if (currentAnim != &downLAnim)
			{
				downLAnim.Reset();
				currentAnim = &downLAnim;
			}
		}
		else {
			if (currentAnim != &downRAnim)
			{
				downRAnim.Reset();
				currentAnim = &downRAnim;
			}
		}
	}
	else if (vistard == false) {
		if (cout <= 0) {
			position.x = position.x + 1; //less speed
			if (currentAnim != &walkRAnim)
			{
				walkRAnim.Reset();
				currentAnim = &walkRAnim;
			}
		}
		else if (cout > 0) {
			if (currentAnim != &Rdead)
			{
				downLAnim.Reset();
				currentAnim = &Rdead;
			}
		}
	}
	else if (vistard == true) {
		if (cout <= 0) {
			position.x = position.x - 1; //less speed
			if (currentAnim != &walkLAnim)
			{
				walkLAnim.Reset();
				currentAnim = &walkLAnim;
			}
		}
		else if (cout > 0) {
			if (currentAnim != &Ldead)
			{
				downLAnim.Reset();
				currentAnim = &Ldead;
			}
		}
	}

	if (hitwallL == true) {
		vistard = false;
		random = (rand() % 4 + 1) * 100;
	}
	else if (hitwallR == true) {
		vistard = true;
		random = (rand() % 4 + 1) * 100;
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}