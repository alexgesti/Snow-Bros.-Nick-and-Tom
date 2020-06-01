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
	return collidersnow;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collidersnow != nullptr && candelete == false) {
		collidersnow->SetPos(position.x, position.y);
		collider->SetPos(position.x, position.y);
	}

	if (hit == true) {
		cout++;
			if (cout == 8) {
				//candelete = true;
				App->audio->PlayFx(destroyedFx);
			}
		hit = false;
	}
	
	/*countdown++;
	if (countdown >= 75) {
		countdown = 0;
		if (cout > 0) {
			cout--;
		}
	}*/

	if (cout > 0) {
		collider->SetPos(-600, -600);
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
}

void Enemy::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collidersnow && c2->type == Collider::Type::PLAYER_SHOT) {
		hit = true;
	}

	if (c1 == collidersnow && c2->type == Collider::Type::FLOOR) {
		gravity = false;
	}
	if (c1 == collidersnow && c2->type == Collider::Type::AIR) {
		gravity = true;
		push = false;
	}
	if (c1 == collidersnow && c2->type == Collider::Type::WALL) {
		hitwallR = true;
	}
	if (c1 == collidersnow && c2->type == Collider::Type::WALL2) {
		hitwallL = true;
	}

	if (cout >= 8) {
		if (c1 == collidersnow && c2->type == Collider::Type::PLAYER) {
			push = true;
		}
	}
}