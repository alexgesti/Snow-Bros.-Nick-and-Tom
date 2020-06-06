#include "Enemy_RedDemon.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

Enemy_RedDemon::Enemy_RedDemon(float x, float y) : Enemy(x, y)
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

	nothing.PushBack({ 0, 0, 0, 0 });

	if (random == 0) {
		vistard = true;
	}
	else if (random == 1) {
		vistard = false;
	}

	collider = App->collisions->AddCollider({ 0, 0, 24, 27 }, Collider::Type::ENEMY);
	cfs = App->collisions->AddCollider({ 0, 0, 22, 24 }, Collider::Type::FISICSNOW, (Module*)App->enemies);
}

void Enemy_RedDemon::Update()
{
	position.x = spawnPos.x + position.x + speed;

	if (cout <= 0) {
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
			speed = 0;
			position.y = spawnPos.y + position.y + 1;
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
		else if (vistard == true) {
			speed = (-0.5f);
			if (currentAnim != &walkLAnim)
			{
				walkLAnim.Reset();
				currentAnim = &walkLAnim;
			}
		}
		else if(vistard == false){
			speed = 0.5f;
			if (currentAnim != &walkRAnim)
			{
				walkRAnim.Reset();
				currentAnim = &walkRAnim;
			}
		}

		if (hitwallL == true) {
			vistard = false;
			random = (rand() % 4 + 1) * 100;
			hitwallL = false;
		}
		else if (hitwallR == true) {
			vistard = true;
			random = (rand() % 4 + 1) * 100;
			hitwallR = false;
		}
	}

	else if (cout > 0 && cout < 8) {
		speed = 0;
		if (gravity == true) {
			position.y = spawnPos.y + position.y + 1;
		}
		
		if (vistard == true) {
			if (currentAnim != &Ldead)
			{
				downLAnim.Reset();
				currentAnim = &Ldead;
			}
		}
		else {
			if (currentAnim != &Rdead)
			{
				downLAnim.Reset();
				currentAnim = &Rdead;
			}
		}
	}

	else if (cout >= 8) {
		speed = 0;
		if (currentAnim != &nothing)
		{
			nothing.Reset();
			currentAnim = &nothing;
		}

		if (gravity == true) {
			position.y = spawnPos.y + position.y + 2;
		}

		if (InitialD == false) {
			if (hitwallL == true) {
				push = false;
				if (vistard == true) {
					speed = 0;
				}
				vistard = false;
				hitwallL = false;
			}
			else if (hitwallR == true) {
				push = false;
				if (vistard == false) {
					speed = 0;
				}
				vistard = true;
				hitwallR = false;
			}
			else {
				if (push == true) {
					if (App->player->vista == true) {
						speed = (-1);		//Misma velocidad que el player
						vistard = true;
					}
					if (App->player->vista == false) {
						speed = 1;		//Misma velocidad que el player
						vistard = false;
					}
				}
			}
			if (up == true) {
				if (vistard == true) {
					speed = (-2);
				}
				if (vistard == false) {
					speed = 2;
				}
				up = false;
			}
		}

		else if (InitialD == true) {
			if (vistard == false) {
				speed = 2;
			}
			if (vistard == true) {
				speed = (-2);
			}

			if (hitwallL == true) {
				vistard = false;
				hitwallL = false;
			}
			else if (hitwallR == true) {
				vistard = true;
				hitwallR = false;
			}
		}
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}