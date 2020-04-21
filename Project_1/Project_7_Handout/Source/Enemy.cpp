#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
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
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && c2->type == Collider::Type::PLAYER_SHOT) {
		count++;
	}

	if (count > 0 && count <= 4) {
		App->particles->AddParticle(App->particles->snow1, position.x+3, position.y+13);
	}
	else if (count > 4 && count <= 6) {
		App->particles->AddParticle(App->particles->snow2, position.x+2, position.y+6);
	}
	else if (count > 6 && count <= 8) {
		App->particles->AddParticle(App->particles->snow3, position.x+1, position.y+4);
	}
	else if (count > 8) {
		App->particles->AddParticle(App->particles->snow4, position.x, position.y);
	}
	if (c1 == collider && c2->type == Collider::Type::PLAYER && count > 8) {
		candelete = true;
		App->audio->PlayFx(destroyedFx);
	}
}