#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"

Enemy::Enemy(float x, float y) : position(x, y)
{
	snow.PushBack({ 592, 816, 1, 1 });
	snow.PushBack({ 14, 703, 22, 31 });
	snow.PushBack({ 43, 703, 24, 31 });
	snow.PushBack({ 75, 703, 25, 31 });
	snow.PushBack({ 142, 703, 25, 31 });

	snowballW.PushBack({ 199, 703, 25, 31 });
	snowballW.PushBack({ 232, 704, 26, 30 });
	snowballW.PushBack({ 266, 704, 25, 30 });
	snowballW.PushBack({ 299, 704, 26, 30 });
	snowballW.loop = true;
	snowballW.speed = 0.5f;

	snowballB.PushBack({ 357, 704, 25, 30 });
	snowballB.PushBack({ 390, 704, 26, 30 });
	snowballB.PushBack({ 424, 703, 25, 31 });
	snowballB.PushBack({ 457, 704, 26, 30 });
	snowballB.loop = true;
	snowballB.speed = 0.5f;

	balldash = App->collisions->AddCollider({ 0, 0, 22, 24 }, Collider::Type::SNOWBALL, (Module*)App->enemies);
	wall1 = App->collisions->AddCollider({ 0, 0, 2, 21 }, Collider::Type::WALL, (Module*)App->enemies);
	wall2 = App->collisions->AddCollider({ 0, 0, 2, 21 }, Collider::Type::WALL2, (Module*)App->enemies);
}

Enemy::~Enemy()
{
	/*if (collider != nullptr)
		collider->pendingToDelete = true;*/
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	//Admin. Collider
	if (cfs != nullptr && candelete == false && InitialD == false) {
		cfs->SetPos(position.x + 4, position.y + 1);
		balldash->SetPos(-600, -600);
		if (cout < 8) {
			wall1->SetPos(-400, -400);
			wall2->SetPos(-400, -400);
			if (cout <= 0) {
				collider->SetPos(position.x, position.y);
			}
		}
	}
	if (cout > 0) {
		collider->SetPos(-600, -600);
		if (InitialD == true) {
			cfs->SetPos(-300, -300);
			balldash->SetPos(position.x + 4, position.y + 1);
		}
	}
	if (InitialD == true){
		countdown++;
		if (countdown >= 5) {
			wall1->SetPos(-400, -400);
			wall2->SetPos(-400, -400);
		}
	}

	//Hit
	if (hit == true) {
		cout++;
		hit = false;
	}

	//CountDown
	if (InitialD == false) {
		if (cout > 0) {
			countdown++;
			if (countdown >= 75) {
				countdown = 0;
				cout--;
			}
		}
	}

	//Animation
	if (push == false || InitialD == false) {
		if (snowAnim != &snow)
		{
			snow.Reset();
			snowAnim = &snow;
		}
		if (cout <= 0) {
			snowAnim->GetSelectedFrame(0);
		}
		else if (cout >= 1 && cout < 4) {
			snowAnim->GetSelectedFrame(1);
		}
		else if (cout >= 4 && cout < 6) {
			snowAnim->GetSelectedFrame(2);
		}
		else if (cout >= 6 && cout < 8) {
			snowAnim->GetSelectedFrame(3);
		}
		else if (cout >= 8) {
			snowAnim->GetSelectedFrame(4);
		}
	}
	else if (kick == true) {			//Does not work
		if (snowAnim != &snowballB)
		{
			snowballB.Reset();
			snowAnim = &snowballB;
		}
	}
	else if (push == true || InitialD == true) {	//Does not work
		if (snowAnim != &snowballW)
		{
			snowballW.Reset();
			snowAnim = &snowballW;
		}
	}

	//Enemy Dead
	if (dead == true) {
		candelete = true;
		App->audio->PlayFx(destroyedFx);
		cfs->SetPos(-300, -300);
		collider->SetPos(-600, -600);
		balldash->SetPos(-600, -600);
		dead = false;
	}
}

void Enemy::Draw()
{
	if (currentAnim != nullptr) {
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
	}
	if (snowAnim != nullptr) {
		App->render->Blit(App->enemies->SnowT, position.x + 2, position.y - 4, &(snowAnim->GetCurrentFrame()));
	}
}

void Enemy::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == cfs && c2->type == Collider::Type::PLAYER_SHOT) {
		hit = true;
	}

	if ((c1 == cfs || c1 == balldash) && c2->type == Collider::Type::FLOOR) {
		gravity = false;
	}
	if ((c1 == cfs || c1 == balldash) && c2->type == Collider::Type::AIR) {
		gravity = true;
		push = false;
	}
	if ((c1 == cfs || c1 == balldash) && c2->type == Collider::Type::WALL) {
		hitwallR = true;
	}
	if ((c1 == cfs || c1 == balldash) && c2->type == Collider::Type::WALL2) {
		hitwallL = true;
	}

	if (cout < 8) {
		if (c1 == cfs && candelete == false && c2->type == Collider::Type::SNOWBALL) {
			dead = true;
		}
	}

	if (cout >= 8) {
		if (c1 == cfs && c2->type == Collider::Type::PLAYER && App->player->jump == false && up == false) {
			push = true;
			App->player->push = true;
			if (hitwallL == true) {
				if (App->player->vista == true) {
					App->player->speedx = 0;
				}
			}
			if (hitwallR == true) {
				if (App->player->vista == false) {
					App->player->speedx = 0;
				}
			}
			if (App->player->shot == true) {
				InitialD = true;
			}
		}

		if (c1 == cfs && c2->type == Collider::Type::PLAYER && App->player->jump == true) { 
			up = true;
		}

		if (c1 == cfs && c2->type == Collider::Type::SNOWBALL && InitialD == false) {
			wall1->SetPos(position.x + 4, position.y + 3);
			wall2->SetPos(position.x + 24, position.y + 3);
			if (c1 == wall1 && c2->type == Collider::Type::SNOWBALL && InitialD == false) {	
				vistard = false;
			}
			else if (c1 == wall2 && c2->type == Collider::Type::SNOWBALL && InitialD == false) {
				vistard = true;
			}
			countdown = 0;
			InitialD = true;
			App->player->kick = true;
		}

		if (c1 == cfs && c2->type == Collider::Type::FEET && App->player->jump == false)
		{
			App->player->gravity = false;
		}

		if (InitialD == true) {
			if (c1 == balldash && candelete == false && c2->type == Collider::Type::DELSNOW) {
				dead = true;
			}

			if (c1 == balldash && c2->type == Collider::Type::FEET) {
				if (App->player->jump == false) {
					App->player->position.x = position.x + 2;
					App->player->position.y = position.y - 1;
					App->player->colliderp->SetPos(600, 600);
					App->player->boulder = true;
				}
			}
		}
	}
}