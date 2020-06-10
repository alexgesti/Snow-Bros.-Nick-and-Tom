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

	Ldead.PushBack({ 15, 41, 28, 26 });
	Ldead.PushBack({ 47, 39, 28, 30 });
	Ldead.speed = 0.1f;

	Rdead.PushBack({ 179, 40, 28, 26 });
	Rdead.PushBack({ 147, 38, 28, 30 });
	Rdead.speed = 0.1f;

	JumpL.PushBack({ 112, 73, 27, 25 });
	JumpL.PushBack({ 50, 69, 23, 30 });
	JumpL.speed = 0.1f;
	JumpL.loop = false;
	
	JumpR.PushBack({ 147, 73, 27, 25 });
	JumpR.PushBack({ 213, 69, 23, 30 });
	JumpR.speed = 0.1f;
	JumpR.loop = false;

	nothing.PushBack({ 0, 0, 0, 0 });

	if (random == 0) {
		vistard = true;
	}
	else if (random == 1) {
		vistard = false;
	}

	collider = App->collisions->AddCollider({ 0, 0, 22, 25 }, Collider::Type::ENEMY);
	cfs = App->collisions->AddCollider({ 0, 0, 22, 24 }, Collider::Type::FISICSNOW, (Module*)App->enemies);
}

void Enemy_RedDemon::Update()
{
	//Admin. Collider
	if (cfs != nullptr && candelete == false && InitialD == false) {
		cfs->SetPos(position.x + 4, position.y + 3);
		balldash->SetPos(-600, -600);
		if (cout < 8) {
			wall1->SetPos(-400, -400);
			wall2->SetPos(-400, -400);
			if (cout <= 0) {
				collider->SetPos(position.x + 4, position.y + 2);
			}
		}
	}
	if (cout > 0) {
		collider->SetPos(-600, -600);
		if (InitialD == true) {
			cfs->SetPos(-300, -300);
			balldash->SetPos(position.x + 4, position.y + 3);
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
			speedx = (-0.5f);
			if (currentAnim != &walkLAnim)
			{
				walkLAnim.Reset();
				currentAnim = &walkLAnim;
			}
		}
		else if(vistard == false){
			speedx = 0.5f;
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
				jumpt = (rand() % 4 + 6) * 100;
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