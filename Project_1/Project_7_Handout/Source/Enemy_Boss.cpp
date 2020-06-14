#include "Enemy_Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"

Enemy_Boss::Enemy_Boss(float x, float y) : Enemy(x, y)
{
	deadboss.PushBack({ 0, 32, 75, 80 });
	deadboss.PushBack({ 238, 32, 93, 80 });
	deadboss.PushBack({ 331, 32, 109, 80 });
	deadboss.speed = 0.05f;
	deadboss.loop = false;

	iddle.PushBack({ 0, 32, 75, 80 });
	iddle.PushBack({ 445, 32, 75, 80 });
	iddle.PushBack({ 525, 32, 75, 80 });
	iddle.PushBack({ 445, 32, 75, 80 });
	iddle.PushBack({ 0, 32, 75, 80 });
	iddle.speed = 0.1f;

	jumpboss.PushBack({ 0, 32, 75, 80 });
	jumpboss.PushBack({ 80, 16, 75, 96 });
	jumpboss.PushBack({ 160, 0, 75, 110 });
	jumpboss.speed = 0.05f; 
	jumpboss.loop = false;

	collider = App->collisions->AddCollider({ 0, 0, 75, 85 }, Collider::Type::ENEMY);
	cfs = App->collisions->AddCollider({ 0, 0, 75, 80 }, Collider::Type::FISICSNOW, (Module*)App->enemies);
	boss = true;
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

	countboss++;

	//Animation
	if (jump == false && dead == false){
		if (currentAnim != &iddle)
		{
			currentAnim = &iddle;
		}
		if (countboss >= 200) {
			one = false;
			App->audio->PlayFx(App->enemies->roarbossFx);
			countboss = 0;
		}
	}
	if (cout >= 25) {
		if (currentAnim != &deadboss)
		{
			currentAnim = &deadboss;
		}
	}

	if (gravity == true) {
		position.y = spawnPos.y + position.y + speedy;
	}

	if (jump == false && gravity == false && dead == false) {
		jumpbt--;
		if (jumpbt <= 0) {
			jump = true;
			gravity = false;
			alt = position.y;
			jumpbt = (rand() % 4 + 3) * 100;
		}
	}
	if (jump == true && dead == false) {
		if (cambio == false) {
			if (position.y > alt - 100) {
				position.y = spawnPos.y + position.y - speedy;
				if (currentAnim != &jumpboss)
				{
					currentAnim = &jumpboss;
				}
			}
			if (position.y <= alt - 100) {
				gravity = true;
				jump = false;
				cambio = true;

				App->audio->PlayFx(App->enemies->spitbossFx);
				calculatexy = (rand() % 6);
				switch (calculatexy) {
				case 0:
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 189);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 113);
					break;
				case 1:
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 151);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 75);
					break;
				case 2:
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 189);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 151);
					break;
				case 3:
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 113);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 75);
					break;
				case 4:
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 189);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 75);
					break;
				case 5:
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 113);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 151);
					break;
				case 6:
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 151);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 75);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 189);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 113);
					break;
				}
			}
		}
		if (cambio == true) {
			if (position.y < alt + 90) {
				position.y = spawnPos.y + position.y + speedy;
				if (currentAnim != &jumpboss)
				{
					currentAnim = &jumpboss;
				}
			}
			if (position.y >= alt + 90) {
				gravity = true;
				cambio = false;
				jump = false;

				App->audio->PlayFx(App->enemies->spitbossFx);
				calculatexy = (rand() % 4);
				switch (calculatexy) {
				case 0:
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 189);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 113);
					break;
				case 1:
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 151);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 75);
					break;
				case 2:
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 189);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 151);
					break;
				case 3:
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 113);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 75);
					break;
				case 4:
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 189);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 75);
					break;
				case 5:
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 113);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 151);
					break;
				case 6:
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 151);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 15, 75);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 189);
					App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, 175, 113);
					break;
				}
			}
		}
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}