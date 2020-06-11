#include "Enemy_SpitFire.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Enemy_SpitFire::Enemy_SpitFire(float x, float y) : Enemy(x, y)
{
	walkRAnim.PushBack({ 198, 3, 18, 26 });
	walkRAnim.PushBack({ 165, 2, 19, 27 });
	walkRAnim.PushBack({ 133, 2, 19, 27 });
	walkRAnim.speed = 0.1f;

	walkLAnim.PushBack({ 40, 3, 18, 26 });
	walkLAnim.PushBack({ 72, 2, 19, 27 });
	walkLAnim.PushBack({ 104, 2, 19, 27 });
	walkLAnim.speed = 0.1f;

	downRAnim.PushBack({ 225, 225, 30 , 30 });

	downLAnim.PushBack({ 1, 225, 30 , 30 });

	Ldead.PushBack({ 1, 69, 28, 25 });
	Ldead.PushBack({ 36, 72, 25, 21 });
	Ldead.speed = 0.1f;

	Rdead.PushBack({ 227, 69, 28, 25 });
	Rdead.PushBack({ 195, 72, 25, 21 });
	Rdead.speed = 0.1f;

	JumpL.PushBack({ 34, 230, 28, 23 });
	JumpL.PushBack({ 38, 96, 22, 31 });
	JumpL.speed = 0.1f;
	JumpL.loop = false;

	JumpR.PushBack({ 194, 230, 28, 23 });
	JumpR.PushBack({ 196, 96, 22, 31 });
	JumpR.speed = 0.1f;
	JumpR.loop = false;

	shootR.PushBack({ 232, 34, 17, 27 });

	shootL.PushBack({ 7, 34, 17, 27 });

	nothing.PushBack({ 0, 0, 0, 0 });

	if (random == 0) {
		vistard = true;
	}
	else if (random == 1) {
		vistard = false;
	}

	collider = App->collisions->AddCollider({ 0, 0, 19, 24 }, Collider::Type::ENEMY);
	cfs = App->collisions->AddCollider({ 0, 0, 19, 24 }, Collider::Type::FISICSNOW, (Module*)App->enemies);
}

void Enemy_SpitFire::Update()
{
	//Admin. Collider
	if (cfs != nullptr && candelete == false && InitialD == false) {
		cfs->SetPos(position.x, position.y + 2);
		balldash->SetPos(-600, -600);
		if (cout < 8) {
			wall1->SetPos(-400, -400);
			wall2->SetPos(-400, -400);
			if (cout <= 0) {
				collider->SetPos(position.x, position.y + 2);
			}
		}
	}
	if (cout > 0) {
		collider->SetPos(-600, -600);
		if (InitialD == true) {
			cfs->SetPos(-300, -300);
			balldash->SetPos(position.x + 2, position.y + 2);
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
		if (random <= 0 && shoot == false) {
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
		else if (vistard == true && shoot == false) {
			speedx = (-0.3f);
			if (currentAnim != &walkLAnim)
			{
				walkLAnim.Reset();
				currentAnim = &walkLAnim;
			}
		}
		else if(vistard == false && shoot == false){
			speedx = 0.3f;
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

		if (jump == false && gravity == false && shoot == false) {
			jumpt--;
			if (jumpt <= 0) {
				jump = true;
				gravity = false;
				alt = position.y;
				jumpt = (rand() % 4 + 11) * 100;
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

		if (jump == false && gravity == false && shoot == false) {
			shoott--;
			if (shoott <= 0) {
				shoot = true;
				speedx = 0;
				shootcd = 40;			//Particle lifetime
				shoott = (rand() % 4 + 1) * 100;
			}
		}
		if (shoot == true) {
			shootcd--;
			if (vistard == true) {
				if (currentAnim != &shootL)
				{
					currentAnim = &shootL;
				}
				if(shootonce == false){
					App->particles->AddParticle(5, App->particles->fireL, position.x - 5, position.y + 4, Collider::Type::ENEMY);
					shootonce = true;
				}
			}
			else {
				if (currentAnim != &shootR)
				{
					currentAnim = &shootR;
				}
				if (shootonce == false) {
					App->particles->AddParticle(6, App->particles->fireR, position.x + 10, position.y + 4, Collider::Type::ENEMY);
					shootonce = true;
				}
			}
			if (shootcd <= 0) {
				shoot = false;
				shootonce = false;
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