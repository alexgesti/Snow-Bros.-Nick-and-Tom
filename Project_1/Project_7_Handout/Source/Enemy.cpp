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

	collider = App->collisions->AddCollider({ 0, 0, 24, 27 }, Collider::Type::ENEMY);
	balldash = App->collisions->AddCollider({ 0, 0, 22, 25 }, Collider::Type::SNOWBALL, (Module*)App->enemies);
}

Enemy::~Enemy()
{
	/*if (collider != nullptr)
		collider->pendingToDelete = true;*/
}

const Collider* Enemy::GetCollider() const
{
	return cfs;
}

const Collider* Enemy::SendCollider() const 
{
	return balldash;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	//Admin. Collider
	if (cfs != nullptr && candelete == false && InitialD == false) {
		cfs->SetPos(position.x + 4, position.y + 1);
		balldash->SetPos(-600, -600);
		if (cout <= 0) {
			collider->SetPos(position.x, position.y);
		}
	}
	if (cout > 0) {
		collider->SetPos(-600, -600);
		if (InitialD == true) {
			cfs->SetPos(-300, -300);
			balldash->SetPos(position.x + 4, position.y + 1);
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

	//Enemy Dead
	if (dead == true) {
		candelete = true;
		App->audio->PlayFx(destroyedFx);
		cfs->SetPos(-600, -600);
		collider->SetPos(-600, -600);
		balldash->SetPos(-600, -600);
		dead = false;
	}
}

void Enemy::Draw()
{
	if (currentAnim != nullptr) {
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
		App->render->Blit(App->enemies->SnowT, position.x + 2, position.y - 4, &(snow.GetCurrentFrame()));
	}

	if (cout <= 0) {
		snow.GetSelectedFrame(0);
	}
	else if (cout >= 1 && cout < 4) {
		snow.GetSelectedFrame(1);
	}
	else if (cout >= 4 && cout < 6) {
		snow.GetSelectedFrame(2);
	}
	else if (cout >= 6 && cout < 8) {
		snow.GetSelectedFrame(3);
	}
	else if (cout >= 8) {
		snow.GetSelectedFrame(4);
	}
	else if (InitialD == true) {
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
		}

		if (c1 == cfs && c2->type == Collider::Type::PLAYER && App->player->jump == true) { 
			up = true;
		}

		if (c1 == cfs && c2->type == Collider::Type::SNOWBALL) {	//Seguir trabajando
			InitialD = true;
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
					App->player->position.x = position.x;
					App->player->position.y = position.y-1;
					App->player->colliderp->SetPos(600, 600);
					App->player->boulder = true;
				}
			}
		}
	}
}