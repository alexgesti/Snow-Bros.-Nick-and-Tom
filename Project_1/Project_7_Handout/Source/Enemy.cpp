#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

Enemy::Enemy(float x, float y) : position(x, y)
{
	snow.PushBack({ 592, 816, 1, 1 });
	snow.PushBack({ 16, 717, 20, 17 });
	snow.PushBack({ 44, 710, 23, 24 });
	snow.PushBack({ 75, 708, 25, 26 });
	snow.PushBack({ 141, 703, 26, 31 });

	collider = App->collisions->AddCollider({ 0, 0, 24, 27 }, Collider::Type::ENEMY);
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

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (cfs != nullptr && candelete == false) {
		cfs->SetPos(position.x + 3, position.y + 1);
		collider->SetPos(position.x, position.y);
	}

	if (hit == true) {
		cout++;
		hit = false;
	}

	if (InitialD == false) {
		if (cout > 0) {
			countdown++;
			if (countdown >= 75) {
				countdown = 0;
				cout--;
			}
		}
	}

	if (cout > 0) {
		collider->SetPos(-600, -600);
	}

	if (dead == true) {
		candelete = true;
		App->audio->PlayFx(destroyedFx);
		cfs->SetPos(-600, -600);
		collider->SetPos(-600, -600);
		dead = false;
	}
}

void Enemy::Draw()
{
	if (currentAnim != nullptr) {
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
		App->render->Blit(App->enemies->SnowT, position.x, position.y, &(snow.GetCurrentFrame()));
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
		//snow.GetSelectedFrame(0);
	}
}

void Enemy::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == cfs && c2->type == Collider::Type::PLAYER_SHOT) {
		hit = true;
	}

	if (c1 == cfs && c2->type == Collider::Type::FLOOR) {
		gravity = false;
	}
	if (c1 == cfs && c2->type == Collider::Type::AIR) {
		gravity = true;
		push = false;
	}
	if (c1 == cfs && c2->type == Collider::Type::WALL) {
		hitwallR = true;
	}
	if (c1 == cfs && c2->type == Collider::Type::WALL2) {
		hitwallL = true;
	}

	if (cout >= 8) {
		if (c1 == cfs && c2->type == Collider::Type::PLAYER) {
			push = true;
		}

		if (c1 == cfs && InitialD == true && candelete == false && c2->type == Collider::Type::DELSNOW) {
			dead = true;
		}

		if (c1 == cfs && InitialD == true && c2->type == Collider::Type::FEET) { //fix
			if (App->player->jump == false) {
				App->player->position.x = position.x;
				App->player->position.y = position.y;
				App->player->colliderf->SetPos(600, 600);
			}
		}
	}
}