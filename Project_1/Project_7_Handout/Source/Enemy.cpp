#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;

	snow.PushBack({ 16, 717, 20, 17 });
	snow.PushBack({ 44, 710, 23, 24 });
	snow.PushBack({ 75, 708, 25, 26 });
	snow.PushBack({ 108, 704, 26, 30 });
	snow.loop = false;
	snow.speed = 0;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	LOG("%d", kills)
	if (kills >= 5) {
		LOG("the end");
	}
}

void Enemy::Draw()
{
	if (currentAnim != nullptr) {
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
		if (cout > 0) {
			App->render->Blit(texture, position.x, position.y, &(snowAnim->GetCurrentFrame()));
		}
	}
}

void Enemy::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && c2->type == Collider::Type::PLAYER_SHOT) {
		cout++;
		snowAnim = &snow;

		if (cout > 0) {
			snow.speed = 0.1f;
			snow.speed = 0.0f;
		}
		else if (cout >= 4) {
			snow.speed = 0.1f;
			snow.speed = 0.0f;
		}
		else if (cout >= 6) {
			snow.speed = 0.1f;
			snow.speed = 0.0f;
		}
		else if (cout >= 8) {
			snow.speed = 0.1f;
			snow.speed = 0.0f;
			candelete = true;
			if (cout == 8) {
				kills++;
			}
			App->audio->PlayFx(destroyedFx);
		}
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