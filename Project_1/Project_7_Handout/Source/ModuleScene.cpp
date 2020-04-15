#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

ModuleScene::ModuleScene()
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/lvl1.png");
	App->audio->PlayMusic("Assets/(Stage 1, 3).ogg", 1.0f);

	//collider suelo
	App->collisions->AddCollider({ 0, 249, 352, 18 }, Collider::Type::FLOOR);			//EL SUELO
	App->collisions->AddCollider({ 0, 211, 87, 5 }, Collider::Type::FLOOR);				//PLAT1 B. IZQ
	App->collisions->AddCollider({ 134, 211, 85, 5 }, Collider::Type::FLOOR);			//PLAT2 B. MED
	App->collisions->AddCollider({ 266, 211, 87, 5 }, Collider::Type::FLOOR);			//PLAT3 B. DER
	App->collisions->AddCollider({ 68, 173, 217, 5 }, Collider::Type::FLOOR);			//PALT4 M. MED GRAND
	App->collisions->AddCollider({ 0, 135, 153, 5 }, Collider::Type::FLOOR);			//PLAT5 ARR. IZQ
	App->collisions->AddCollider({ 200, 135, 152, 5 }, Collider::Type::FLOOR);			//PLAT6 ARR. DER
	App->collisions->AddCollider({ 45, 98, 43, 5 }, Collider::Type::FLOOR);				//PLAT7 GRAND. IZQ
	App->collisions->AddCollider({ 88, 79, 177, 5 }, Collider::Type::FLOOR);			//PLAT9 GRAND. MEDIO
	App->collisions->AddCollider({ 265, 98, 42, 5 }, Collider::Type::FLOOR);			//PALT11 GRAND. DER


	//collider de los lados
	App->collisions->AddCollider({ 88, 84, 4, 15 }, Collider::Type::WALL);				//PALT8 GRAND. MURO IZQ
	App->collisions->AddCollider({ 261, 84, 4, 15 }, Collider::Type::WALL);				//PLAT10 GRAND. MURO DER
	App->collisions->AddCollider({ 0, 19, 3, 245 }, Collider::Type::WALL);				//MURO IZQ
	App->collisions->AddCollider({ 350, 19, 3, 245 }, Collider::Type::WALL);			//MURO DER

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 30, 220);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 625, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 640, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 665, 80);

	
	return ret;
}

update_status ModuleScene::Update()
{

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	SDL_Rect bgrect;
	bgrect.w = SCREEN_SIZE;
	App->render->Blit(bgTexture,0,0, NULL);

	return update_status::UPDATE_CONTINUE;
}