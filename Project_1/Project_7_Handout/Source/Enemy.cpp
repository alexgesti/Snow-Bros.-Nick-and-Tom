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

	snow.PushBack({ 16, 717, 20, 17 });
	snow.PushBack({ 44, 710, 23, 24 });
	snow.PushBack({ 75, 708, 25, 26 });
	snow.PushBack({ 108, 704, 26, 30 });
	snow.loop = false;
	snow.speed = 0.1f;
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

	if (hit == true) {
		cout++;
		LOG("%d", cout)

		if (cout == 1 || cout == 4 || cout == 6) {
			snow.Update();
		}
		if (cout == 8) {
			snow.Update();
			candelete = true;
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
	if (cout > 0) {
		//App->render->Blit(texture, position.x, position.y, &(snowAnim->GetCurrentFrame()));
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