#include "Enemy_Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

Enemy_Boss::Enemy_Boss(float x, float y) : Enemy(x, y)
{
	jumpboss.PushBack({ 0, 32, 75, 80 });
	deadboss.PushBack({ 238, 32, 93, 80 });
	deadboss.PushBack({ 331, 65, 109, 47 });
	deadboss.speed = 0.1f;
	deadboss.loop = false;

	iddle.PushBack({ 0, 32, 75, 80 });

	jumpboss.PushBack({ 0, 32, 75, 80 });
	jumpboss.PushBack({ 80, 16, 75, 96 });
	jumpboss.PushBack({ 160, 0, 75, 110 });
	jumpboss.speed = 0.1f; 
	jumpboss.loop = false;

	collider = App->collisions->AddCollider({ 0, 0, 22, 25 }, Collider::Type::ENEMY);
	cfs = App->collisions->AddCollider({ 0, 0, 22, 24 }, Collider::Type::FISICSNOW, (Module*)App->enemies);
	boss = true;

	//Cambiar animaciones e imagen
}

void Enemy_Boss::Update()
{
	if (cfs != nullptr && candelete == false) {
		cfs->SetPos(position.x, position.y);
		collider->SetPos(position.x, position.y);
		balldash->SetPos(-600, -600);
		wall1->SetPos(-400, -400);
		wall2->SetPos(-400, -400);
	}

	if (jump == false){
		if (currentAnim != &iddle)
		{
			currentAnim = &iddle;
		}
	}
	if (cout >= 15) {
		if (currentAnim != &deadboss)
		{
			currentAnim = &deadboss;
		}
		dead = true;
	}

	if (jump == false && gravity == false) {
		jumpbt--;
		if (jumpbt <= 0) {
			jump = true;
			gravity = false;
			alt = position.y;
			jumpbt = (rand() % 4 + 11) * 100;
		}
	}
	if (jump == true) {
		if (cambio == false) {
			if (position.y > alt - 80) {
				position.y = spawnPos.y + position.y - speedy;
				if (currentAnim != &jumpboss)
				{
					currentAnim = &jumpboss;
				}
			}
			if (position.y <= alt - 80) {
				gravity = true;
				jump = false;
				cambio = true;
			}
		}
		if (cambio == false) {
			if (position.y > alt - 10) {
				position.y = spawnPos.y + position.y - speedy;
				if (currentAnim != &jumpboss)
				{
					currentAnim = &jumpboss;
				}
			}
			if (position.y >= alt + 50) {
				gravity = true;
				jump = false;
				cambio = false;
			}
		}
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}