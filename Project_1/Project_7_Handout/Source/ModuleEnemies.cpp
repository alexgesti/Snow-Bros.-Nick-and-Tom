#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleChangeScene.h"
#include "ModulePlayer.h"

#include "Enemy.h"
#include "Enemy_RedDemon.h"
#include "Enemy_YellowMonkey.h"
#include "Enemy_SpitFire.h"
#include "Enemy_Boss.h"
#include "Enemy_MiniBoss.h"

#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	Redemon = App->textures->Load("Assets/demonio.png");
	YellMonky = App->textures->Load("Assets/monono.png");
	SF = App->textures->Load("Assets/Rana.png");
	SnowT = App->textures->Load("Assets/Nick&Tom.png");
	bos = App->textures->Load("Assets/boss_1.png");
	mbos = App->textures->Load("Assets/miniboss.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/EnemyFlying.wav");
	snowDestroyedFx = App->audio->LoadFx("Assets/snowdel.wav");
	choqueFx = App->audio->LoadFx("Assets/rebotar.wav");
	pydFx = App->audio->LoadFx("Assets/patada y rebote.wav");
	roarbossFx = App->audio->LoadFx("Assets/roarboss.wav");;
	spitbossFx = App->audio->LoadFx("Assets/spit.wav");;

	kills = 0;

	return true;
}

update_status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr) {
			enemies[i]->Update();

			if (enemies[i]->boss == true) {
				changboss = true;
			}
		}
	}

	if (kills >= en && changboss == false)
	{
		App->change->Changing((Module*)App->sceneLevel_1, (Module*)App->sceneWin, 60);
	}
	if (kills >= 1 && changboss == true)
	{
		App->change->Changing((Module*)App->sceneLevel_1, (Module*)App->sceneWin, 60);
	}

	HandleEnemiesDespawn();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	App->textures->Unload(Redemon);

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, float x, float y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
				en++;
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->candelete == true && changboss == false)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				delete enemies[i];
				enemies[i] = nullptr;
				kills++;
			}
			else if (enemies[i]->candelete == true && changboss == true)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				delete enemies[i];
				enemies[i] = nullptr;
			}
			else if (enemies[i]->bdelete == true && changboss == true)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				enemies[i] = nullptr;
				kills++;
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
			case ENEMY_TYPE::REDDEMON:
				enemies[i] = new Enemy_RedDemon(info.x, info.y);
				enemies[i]->texture = Redemon;
				break;
			case ENEMY_TYPE::YELLOWMONKEY:
				enemies[i] = new Enemy_YellowMonkey(info.x, info.y);
				enemies[i]->texture = YellMonky;
				break;
			case ENEMY_TYPE::SPITFIRE:
				enemies[i] = new Enemy_SpitFire(info.x, info.y);
				enemies[i]->texture = SF;
				break;
			case ENEMY_TYPE::BOSS:
				enemies[i] = new Enemy_Boss(info.x, info.y);
				enemies[i]->texture = bos;
				break;
			case ENEMY_TYPE::MINIBOSS:
				enemies[i] = new Enemy_MiniBoss(info.x, info.y);
				enemies[i]->texture = mbos;
				break;
			}

			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->OnCollision(c1, c2);//Notify the enemy of a collision

			if (enemies[i]->candelete == true && enemies[i]->once) {
				enemies[i]->once = false;
				break;
			}
		}
	}
}