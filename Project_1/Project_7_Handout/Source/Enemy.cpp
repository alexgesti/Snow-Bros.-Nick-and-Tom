#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Enemy::~Enemy()
{
	/*if (collider != nullptr)
		collider->pendingToDelete = true;*/
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr && candelete == false)
		collider->SetPos(position.x, position.y);

	if (hit == true) {
		cout++;

		if (cout == 8) {
			candelete = true;
			collider->SetPos(-600, -600);
			App->audio->PlayFx(destroyedFx);
		}
		hit = false;
	}
}

void Enemy::Draw()
{
	if (currentAnim != nullptr) {
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
	}
}

void Enemy::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && c2->type == Collider::Type::PLAYER_SHOT) {
		hit = true;
	}

	if (c1 == collider && c2->type == Collider::Type::FLOOR) {
		gravity = false;
	}
	if (c1 == collider && c2->type == Collider::Type::AIR) {
		gravity = true;
		hitwallL = false;
		hitwallR = false;
	}
	if (c1 == collider && c2->type == Collider::Type::WALL) {
		hitwallR = true;
	}
	if (c1 == collider && c2->type == Collider::Type::WALL2) {
		hitwallL = true;
	}
}