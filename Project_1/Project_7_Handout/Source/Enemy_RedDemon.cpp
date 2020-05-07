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

	Ldead1.PushBack({ 46, 236, 28, 30 });
	Ldead1.PushBack({ 78, 234, 28, 30 });
	Ldead1.speed = 0.1f;

	Rdead1.PushBack({ 210, 235, 28, 31 });
	Rdead1.PushBack({ 178, 233, 28, 31 });
	Rdead1.speed = 0.1f;

	Ldead2.PushBack({ 46, 274, 28, 30 });
	Ldead2.PushBack({ 78, 272, 28, 30 });
	Ldead2.speed = 0.1f;

	Rdead2.PushBack({ 210, 273, 28, 31 });
	Rdead2.PushBack({ 178, 271, 28, 31 });
	Rdead2.speed = 0.1f;

	Ldead3.PushBack({ 46, 315, 28, 30 });
	Ldead3.PushBack({ 78, 313, 28, 30 });
	Ldead3.speed = 0.1f;

	Rdead3.PushBack({ 210, 314, 28, 31 });
	Rdead3.PushBack({ 178, 312, 28, 31 });
	Rdead3.speed = 0.1f;

	snowball.PushBack({ 129, 275, 26, 30 });

	if (random == 0) {
		path.PushBack({ 0.5f, 0 }, (rand() % 4 + 1) * 100, &walkRAnim);
		path.PushBack({ -0.5f, 0 }, (rand() % 4 + 1) * 100, &walkLAnim);
	}
	if (random == 1) {
		path.PushBack({ -0.5f, 0 }, (rand() % 4 + 1) * 100, &walkLAnim);
		path.PushBack({ 0.5f, 0 }, (rand() % 4 + 1) * 100, &walkRAnim);
	}

	collider = App->collisions->AddCollider({ 0, 0, 24, 27 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedDemon::Update()
{
	path.Update();

	if (cout <= 0 || gravity == true) {
		if (path.GetCurrentAnimation() == &walkLAnim) {
			vistard = true;
		}
		else {
			vistard = false;
		}
	}

	if (hitwallL == true) {
		position.x += 1;
		hitwallL = false;
	}
	else if (hitwallR == true) {
		position.x -= 1;
		hitwallR = false;
	}

	if (gravity == true) {
		position.y += 1;
		movement.y += 1;
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
	else if (cout <= 0) {
		position = path.GetRelativePosition() + movement + spawnPos;
		currentAnim = path.GetCurrentAnimation();
	}
	else if (cout > 0) {
		if (vistard == true) {
			if (cout > 0 && cout < 4) {
				if (currentAnim != &Ldead1)
				{
					Ldead1.Reset();
					currentAnim = &Ldead1;
				}
			}
			if (cout >= 4 && cout < 6) {
				if (currentAnim != &Ldead2)
				{
					Ldead2.Reset();
					currentAnim = &Ldead2;
				}
			}
			if (cout >= 6 && cout < 8) {
				if (currentAnim != &Ldead3)
				{
					Ldead3.Reset();
					currentAnim = &Ldead3;
				}
			}
			if (cout >= 8) {
				if (currentAnim != &snowball)
				{
					snowball.Reset();
					currentAnim = &snowball;
				}
			}
		}
		else {
			if (cout > 0 && cout < 4) {
				if (currentAnim != &Rdead1)
				{
					Rdead1.Reset();
					currentAnim = &Rdead1;
				}
			}
			if (cout >= 4 && cout < 6) {
				if (currentAnim != &Rdead2)
				{
					Rdead2.Reset();
					currentAnim = &Rdead2;
				}
			}
			if (cout >= 6 && cout < 8) {
				if (currentAnim != &Rdead3)
				{
					Rdead3.Reset();
					currentAnim = &Rdead3;
				}
			}
			if (cout >= 8) {
				if (currentAnim != &snowball)
				{
					snowball.Reset();
					currentAnim = &snowball;
				}
			}
		}
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
