#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "ModulePoints.h"

#include "SDL/include/SDL_mouse.h"
#include "SDL/include/SDL_scancode.h"

ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{
	fase.PushBack({ 122, 28, 12, 15 });

	alive.PushBack({ 25, 63, 8, 8 });
	alive.PushBack({ 17, 63, 7, 8 });
	alive.PushBack({ 11, 63, 5, 8 });
}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	camscene = 9;

	bool ret = true;
	if (camscene == 0) {
		bgTexture = App->textures->Load("Assets/lvl1.png");
	}
	else if (camscene == 1) {
		//bgTexture = App->textures->Load("Assets/lvl1.png");
	}
	else if (camscene == 2) {
		//bgTexture = App->textures->Load("Assets/lvl1.png");
	}
	else if (camscene == 3) {
		//bgTexture = App->textures->Load("Assets/lvl1.png");
	}
	else if (camscene == 4) {
		//bgTexture = App->textures->Load("Assets/lvl1.png");
	}
	else if (camscene == 5) {
		//bgTexture = App->textures->Load("Assets/lvl1.png");
	}
	else if (camscene == 6) {
		//bgTexture = App->textures->Load("Assets/lvl1.png");
	}
	else if (camscene == 7) {
		//bgTexture = App->textures->Load("Assets/lvl1.png");
	}
	else if (camscene == 8) {
		//bgTexture = App->textures->Load("Assets/lvl1.png");
	}
	else if (camscene == 9) {
		bgTexture = App->textures->Load("Assets/lvl10.1.png");
	}

	face = App->textures->Load("Assets/Nick&Tom.png");
	numbers = App->textures->Load("Assets/Title_ToplanRights.png");

	App->audio->PlayMusic("Assets/(Stage 1, 3).ogg", 1.0f);

	//collider del aire para los saltos
	if (camscene == 0) {
		App->collisions->AddCollider({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::AIR);	//EL AIRE

		App->collisions->AddCollider({ 0, 247, 352, 18 }, Collider::Type::FLOOR);			//EL SUELO
		App->collisions->AddCollider({ 0, 209, 87, 2 }, Collider::Type::FLOOR);				//PLAT1 B. IZQ
		App->collisions->AddCollider({ 134, 209, 85, 2 }, Collider::Type::FLOOR);			//PLAT2 B. MED
		App->collisions->AddCollider({ 266, 209, 87, 2 }, Collider::Type::FLOOR);			//PLAT3 B. DER
		App->collisions->AddCollider({ 68, 170, 217, 2 }, Collider::Type::FLOOR);			//PALT4 M. MED GRAND
		App->collisions->AddCollider({ 0, 134, 153, 2 }, Collider::Type::FLOOR);			//PLAT5 ARR. IZQ
		App->collisions->AddCollider({ 200, 134, 152, 2 }, Collider::Type::FLOOR);			//PLAT6 ARR. DER
		App->collisions->AddCollider({ 45, 96, 43, 2 }, Collider::Type::FLOOR);				//PLAT7 GRAND. IZQ
		App->collisions->AddCollider({ 88, 77, 177, 2 }, Collider::Type::FLOOR);			//PLAT9 GRAND. MEDIO
		App->collisions->AddCollider({ 265, 96, 42, 2 }, Collider::Type::FLOOR);			//PALT11 GRAND. DER


		//collider de los lados
		App->collisions->AddCollider({ 88, 84, 4, 15 }, Collider::Type::WALL);				//PALT8 GRAND. MURO IZQ
		App->collisions->AddCollider({ 261, 84, 4, 15 }, Collider::Type::WALL2);			//PLAT10 GRAND. MURO DER
		App->collisions->AddCollider({ 0, 19, 3, 245 }, Collider::Type::WALL2);				//MURO IZQ
		App->collisions->AddCollider({ 350, 19, 3, 245 }, Collider::Type::WALL);			//MURO DER

		//Deletear la SnowBall
		App->collisions->AddCollider({ 0, 225, 5, 20 }, Collider::Type::DELSNOW);
		App->collisions->AddCollider({ 348, 225, 5, 20 }, Collider::Type::DELSNOW);

		// Enemies ---
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 100, 50);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 230, 50);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 70, 106);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 250, 106);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 90, 143);
	}
	else if (camscene == 1) {

	}
	else if (camscene == 2) {

	}
	else if (camscene == 3) {

	}
	else if (camscene == 4) {

	}
	else if (camscene == 5) {

	}
	else if (camscene == 6) {

	}
	else if (camscene == 7) {

	}
	else if (camscene == 8) {

	}
	else if (camscene == 9) {
		App->collisions->AddCollider({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::AIR);    //EL AIRE

		App->collisions->AddCollider({ 0, 247, 352, 18 }, Collider::Type::FLOOR);            //EL SUELO
		App->collisions->AddCollider({ 68, 209, 130, 2 }, Collider::Type::FLOOR);            //BAJO IZQUIERDA
		App->collisions->AddCollider({ 0, 171, 154, 2 }, Collider::Type::FLOOR);            //BAJO MEDIO IZQUIERDA
		App->collisions->AddCollider({ 68, 133, 130, 2 }, Collider::Type::FLOOR);            //MEDIO IZQUIERDA
		App->collisions->AddCollider({ 0, 95, 154, 2 }, Collider::Type::FLOOR);                //ALTO MEDIO IZQUIERDA
		App->collisions->AddCollider({ 245, 152, 154, 2 }, Collider::Type::FLOOR);            //MEDIO/2 DERECHA

		//Collider de los lados
		App->collisions->AddCollider({ 0, 0, 8, 275 }, Collider::Type::WALL2);                //MURO IZQ
		App->collisions->AddCollider({ 345, 0, 8, 275 }, Collider::Type::WALL);                //MURO DER

		//Deletear la SnowBall
		App->collisions->AddCollider({ 0, 225, 10, 20 }, Collider::Type::DELSNOW);
		App->collisions->AddCollider({ 343, 225, 10, 20 }, Collider::Type::DELSNOW);

		// Enemies ---
		App->enemies->AddEnemy(ENEMY_TYPE::BOSS, 250, 170);
	}

	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();

	alive.GetSelectedFrame(0);
	
	return ret;
}

update_status ModuleScene::Update()
{
	if (App->player->lives == 3) {
		alive.GetSelectedFrame(0);
	}
	else if (App->player->lives == 2) {
		alive.GetSelectedFrame(1);
	}
	else if (App->player->lives == 1) {
		alive.GetSelectedFrame(2);
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_DOWN) {
		return update_status::UPDATE_STOP;
	}

	if (App->input->keys[SDL_SCANCODE_KP_0] == KEY_STATE::KEY_DOWN)
	{
		enemy = 0;
	}
	if (App->input->keys[SDL_SCANCODE_KP_1] == KEY_STATE::KEY_DOWN)
	{
		enemy = 1;
	}
	if (App->input->keys[SDL_SCANCODE_KP_2] == KEY_STATE::KEY_DOWN)
	{
		enemy = 2;
	}
	if (App->input->keys[SDL_SCANCODE_KP_3] == KEY_STATE::KEY_DOWN)
	{
		enemy = 3;
	}
	if (App->input->keys[SDL_SCANCODE_KP_4] == KEY_STATE::KEY_DOWN)
	{
		enemy = 4;
	}
	if (App->input->keys[SDL_SCANCODE_KP_5] == KEY_STATE::KEY_DOWN)
	{
		enemy = 5;
	}

	check = false;
	if (SDL_GetMouseState(&xm, &ym) && SDL_BUTTON(SDL_BUTTON_LEFT)) {
		check = true;
	}
	if (SDL_GetMouseState(&xm, &ym) && SDL_BUTTON(SDL_BUTTON_LEFT) && once == false) {
		if (enemy == 1) {
			App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, xm, ym);
		}
		if (enemy == 2) {
			App->enemies->AddEnemy(ENEMY_TYPE::YELLOWMONKEY, xm, ym);
		}
		if (enemy == 3) {
			App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, xm, ym);
		}
		if (enemy == 4) {
			App->enemies->AddEnemy(ENEMY_TYPE::MINIBOSS, xm, ym);
		}
		if (enemy == 5) {
			App->enemies->AddEnemy(ENEMY_TYPE::BOSS, xm, ym);
		}
		once = true;
	}
	if (check == false) {
		once = false;
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	SDL_Rect bgrect;
	bgrect.w = SCREEN_SIZE;
	App->render->Blit(bgTexture, 0, 0, NULL);

	App->render->Blit(face, 24, 20, &(fase.GetCurrentFrame()));
	App->render->Blit(numbers, 40, 23, &(alive.GetCurrentFrame()));
	App->points->returnPoints();

	if (App->input->debugGamepadInfo == true) App->input->DebugDrawGamepadInfo();

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();

	App->textures->Unload(bgTexture);
	App->textures->Unload(face);
	App->textures->Unload(numbers);
	App->textures->Unload(App->player->texture);
	App->enemies->CleanUp();
	App->collisions->CleanUp();
	App->audio->PlayMusic(NULL);

	return true;
}