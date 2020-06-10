#include "Enemy_YellowMonkey.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

Enemy_YellowMonkey::Enemy_YellowMonkey(float x, float y) : Enemy(x, y)
{
	walkRAnim.PushBack({ 328, 0, 35, 32 });
	walkRAnim.PushBack({ 433, 2, 33, 30 });
	walkRAnim.PushBack({ 382, 3, 31, 29 });
	walkRAnim.speed = 0.2f;

	walkLAnim.PushBack({ 159, 0, 35, 32 });
	walkLAnim.PushBack({ 56, 2, 33, 30 });
	walkLAnim.PushBack({ 109, 3, 31, 29 });
	walkLAnim.speed = 0.2f;

	downRAnim.PushBack({ 484, 156, 35 , 36 });

	downLAnim.PushBack({ 3, 156, 35 , 36 });

	Ldead.PushBack({ 213, 5, 32, 28 });
	Ldead.PushBack({ 6, 57, 32, 28 });
	Ldead.speed = 0.1f;

	Rdead.PushBack({ 277, 5, 32, 28 });
	Rdead.PushBack({ 484, 57, 32, 28 });
	Rdead.speed = 0.1f;

	JumpL.PushBack({ 57, 162, 29, 26 });
	JumpL.PushBack({ 111, 52, 24, 36 });
	JumpL.speed = 0.1f;
	JumpL.loop = false;

	JumpR.PushBack({ 436, 162, 29, 26 });
	JumpR.PushBack({ 387, 52, 24, 36 });
	JumpR.speed = 0.1f;
	JumpR.loop = false;

	nothing.PushBack({ 0, 0, 0, 0 });

	if (random == 0) {
		vistard = true;
	}
	else if (random == 1) {
		vistard = false;
	}

	collider = App->collisions->AddCollider({ 0, 0, 24, 25 }, Collider::Type::ENEMY);
	cfs = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::FISICSNOW, (Module*)App->enemies);
}

void Enemy_YellowMonkey::Update()
{
	//Admin. Collider
	if (cfs != nullptr && candelete == false && InitialD == false) {
		cfs->SetPos(position.x + 2, position.y + 5);
		balldash->SetPos(-600, -600);
		if (cout < 8) {
			wall1->SetPos(-400, -400);
			wall2->SetPos(-400, -400);
			if (cout <= 0) {
				collider->SetPos(position.x + 2, position.y + 4);
			}
		}
	}
	if (cout > 0) {
		collider->SetPos(-600, -600);
		if (InitialD == true) {
			cfs->SetPos(-300, -300);
			balldash->SetPos(position.x + 4, position.y + 5);
		}
	}
	if (InitialD == true) {
		countdown++;
		if (countdown >= 5) {
			wall1->SetPos(-400, -400);
			wall2->SetPos(-400, -400);
		}
	}

	position.x = spawnPos.x + position.x + speedx;

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
			speedx = 0;
			position.y = spawnPos.y + position.y + speedy;
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
			speedx = (-1);
			if (currentAnim != &walkLAnim)
			{
				walkLAnim.Reset();
				currentAnim = &walkLAnim;
			}
		}
		else if(vistard == false){
			speedx = 1;
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

		if (jump == false && gravity == false) {
			jumpt--;
			if (jumpt <= 0) {
				jump = true;
				gravity = false;
				alt = position.y;
				jumpt = (rand() % 4 + 1) * 100;
			}
		}

		if (jump == true) {
			if (position.y > alt - 40) {
				speedx = 0;
				position.y = spawnPos.y + position.y - speedy;
				if (vistard == true) {
					if (currentAnim != &JumpL)
					{
						currentAnim = &JumpL;
					}
				}
				else {
					if (currentAnim != &JumpR)
					{
						currentAnim = &JumpR;
					}
				}
			}
			if (position.y <= alt - 40){
				gravity = true;
				jump = false;
			}
		}
	}

	else if (cout > 0 && cout < 8) {
		jump = false;
		speedx = 0;
		if (gravity == true) {
			position.y = spawnPos.y + position.y + speedy;
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
		speedx = 0;
		if (currentAnim != &nothing)
		{
			nothing.Reset();
			currentAnim = &nothing;
		}

		if (gravity == true) {
			position.y = spawnPos.y + position.y + (speedy*2);
		}

		if (InitialD == false) {
			if (hitwallL == true) {
				push = false;
				if (vistard == true) {
					speedx = 0;
				}
				vistard = false;
				hitwallL = false;
			}
			else if (hitwallR == true) {
				push = false;
				if (vistard == false) {
					speedx = 0;
				}
				vistard = true;
				hitwallR = false;
			}
			else {
				if (push == true) {
					if (App->player->vista == true) {
						speedx = (-1);		//Misma velocidad que el player
						vistard = true;
					}
					if (App->player->vista == false) {
						speedx = 1;		//Misma velocidad que el player
						vistard = false;
					}
				}
			}
			if (up == true) {
				if (vistard == true) {
					speedx = (-2);
				}
				if (vistard == false) {
					speedx = 2;
				}
				up = false;
			}
		}

		else if (InitialD == true) {
			if (vistard == false) {
				speedx = 2;
			}
			if (vistard == true) {
				speedx = (-2);
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