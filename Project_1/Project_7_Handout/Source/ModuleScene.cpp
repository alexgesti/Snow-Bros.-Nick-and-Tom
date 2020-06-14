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
#include <stdio.h>

#include "SDL/include/SDL_mouse.h"
#include "SDL/include/SDL_scancode.h"

ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{
	name = "Gameplay";

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

	bool ret = true;
	if (camscene == 0) {
		bgTexture = App->textures->Load("Assets/lvl1.png");
	}
	else if (camscene == 1) {
		bgTexture = App->textures->Load("Assets/lvl2.png");
	}
	else if (camscene == 2) {
		bgTexture = App->textures->Load("Assets/lvl3.png");
	}
	else if (camscene == 3) {
		bgTexture = App->textures->Load("Assets/lvl4.png");
	}
	else if (camscene == 4) {
		bgTexture = App->textures->Load("Assets/lvl5.png");
	}
	else if (camscene == 5) {
		bgTexture = App->textures->Load("Assets/lvl6.png");
	}
	else if (camscene == 6) {
		bgTexture = App->textures->Load("Assets/lvl7.png");
	}
	else if (camscene == 7) {
		bgTexture = App->textures->Load("Assets/lvl8.png");
	}
	else if (camscene == 8) {
		bgTexture = App->textures->Load("Assets/lvl9.png");
	}
	else if (camscene == 9) {
		bgTexture = App->textures->Load("Assets/lvl10.1.png");
	}

	face = App->textures->Load("Assets/Nick&Tom.png");
	numbers = App->textures->Load("Assets/Title_ToplanRights.png");

	if (camscene == 9) App->audio->PlayMusic("Assets/Boss_1.ogg", 1.0f);
	else App->audio->PlayMusic("Assets/(Stage 1, 3).ogg", 1.0f);

	//collider del aire para los saltos
	if (camscene == 0) {
		App->collisions->AddCollider({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::AIR);	//EL SUELO

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
		App->collisions->AddCollider({ 0, 19, 3, 275 }, Collider::Type::WALL2);				//MURO IZQ
		App->collisions->AddCollider({ 350, 19, 3, 275 }, Collider::Type::WALL);			//MURO DER

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
		App->collisions->AddCollider({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::AIR);	//EL AIRE

		App->collisions->AddCollider({ 0, 247, 352, 18 }, Collider::Type::FLOOR);			//EL SUELO
		App->collisions->AddCollider({ 87, 209, 199, 2 }, Collider::Type::FLOOR);			//BAJO
		App->collisions->AddCollider({ 133, 171, 133, 2 }, Collider::Type::FLOOR);			//BAJO MED
		App->collisions->AddCollider({ 87, 133, 133, 2 }, Collider::Type::FLOOR);			//MEDIO
		App->collisions->AddCollider({ 133, 95, 133, 2 }, Collider::Type::FLOOR);			//ARRIBA MEDIO
		App->collisions->AddCollider({ 67, 57, 153, 2 }, Collider::Type::FLOOR);			//ARRIBA

		App->collisions->AddCollider({ 45, 171, 42, 2 }, Collider::Type::FLOOR);			//BAJO MED PLAT
		App->collisions->AddCollider({ 266, 133, 43, 2 }, Collider::Type::FLOOR);			//MEDIO PLAT
		App->collisions->AddCollider({ 45, 95, 42, 2 }, Collider::Type::FLOOR);				//ARRIBA MEDIO PLAT
		App->collisions->AddCollider({ 266, 57, 43, 2 }, Collider::Type::FLOOR);			//ARRIBA PLAT

		//collider de los lados
		App->collisions->AddCollider({ 83, 173, 4, 38 }, Collider::Type::WALL2);			//BAJO
		App->collisions->AddCollider({ 83, 97, 4, 38 }, Collider::Type::WALL2);				//ARRIBA MEDIO
		App->collisions->AddCollider({ 266, 135, 4, 38 }, Collider::Type::WALL);			//MEDIO
		App->collisions->AddCollider({ 266, 59, 4, 38 }, Collider::Type::WALL);				//ARRIBA

		App->collisions->AddCollider({ 0, 0, 8, 275 }, Collider::Type::WALL2);				//MURO IZQ
		App->collisions->AddCollider({ 345, 0, 8, 275 }, Collider::Type::WALL);				//MURO DER

		//Deletear la SnowBall
		App->collisions->AddCollider({ 0, 225, 10, 20 }, Collider::Type::DELSNOW);
		App->collisions->AddCollider({ 343, 225, 10, 20 }, Collider::Type::DELSNOW);

		// Enemies ---
		App->enemies->AddEnemy(ENEMY_TYPE::YELLOWMONKEY, 67, 29);
		App->enemies->AddEnemy(ENEMY_TYPE::YELLOWMONKEY, 152, 29);
		App->enemies->AddEnemy(ENEMY_TYPE::YELLOWMONKEY, 232, 143);
		App->enemies->AddEnemy(ENEMY_TYPE::YELLOWMONKEY, 90, 181);
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 202, 70);

	}
	else if (camscene == 2) {
		App->collisions->AddCollider({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::AIR);	//EL AIRE

		App->collisions->AddCollider({ 0, 247, 352, 18 }, Collider::Type::FLOOR);			//EL SUELO
		App->collisions->AddCollider({ 112, 209, 130, 2 }, Collider::Type::FLOOR);			//BAJO
		App->collisions->AddCollider({ 0, 209, 65, 2 }, Collider::Type::FLOOR);				//BAJO IZQUIERDA
		App->collisions->AddCollider({ 289, 209, 65, 2 }, Collider::Type::FLOOR);			//BAJO DERECHA
		App->collisions->AddCollider({ 156, 171, 42, 2 }, Collider::Type::FLOOR);			//BAJO MEDIO
		App->collisions->AddCollider({ 0, 171, 21, 2 }, Collider::Type::FLOOR);				//BAJO MEDIO IZQUIERDA
		App->collisions->AddCollider({ 333, 171, 21, 2 }, Collider::Type::FLOOR);			//BAJO MEDIO DERECHA
		App->collisions->AddCollider({ 156, 133, 42, 2 }, Collider::Type::FLOOR);			//MEDIO
		App->collisions->AddCollider({ 0, 133, 21, 2 }, Collider::Type::FLOOR);				//MEDIO IZQUIERDA
		App->collisions->AddCollider({ 333, 133, 21, 2 }, Collider::Type::FLOOR);			//MEDIO DERECHA
		App->collisions->AddCollider({ 68, 133, 41, 2 }, Collider::Type::FLOOR);			//MEDIO MEDIO IZQUIERDA
		App->collisions->AddCollider({ 244, 133, 41, 2 }, Collider::Type::FLOOR);			//MEDIO MEDIO DERECHA
		App->collisions->AddCollider({ 0, 95, 43, 2 }, Collider::Type::FLOOR);				//ALTO MEDIO IZQUIERDA
		App->collisions->AddCollider({ 311, 95, 43, 2 }, Collider::Type::FLOOR);			//ALTO MEDIO DERECHA
		App->collisions->AddCollider({ 90, 95, 174, 2 }, Collider::Type::FLOOR);			//ALTO MEDIO 
		App->collisions->AddCollider({ 68, 57, 218, 2 }, Collider::Type::FLOOR);			//ALTO 

		//Collider de los lados
		App->collisions->AddCollider({ 0, 0, 8, 275 }, Collider::Type::WALL2);				//MURO IZQ
		App->collisions->AddCollider({ 345, 0, 8, 275 }, Collider::Type::WALL);				//MURO DER

		//Deletear la SnowBall
		App->collisions->AddCollider({ 0, 225, 10, 20 }, Collider::Type::DELSNOW);
		App->collisions->AddCollider({ 343, 225, 10, 20 }, Collider::Type::DELSNOW);

		// Enemies ---
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 20, 183);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 305, 183);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 250, 107);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 74, 107);
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 315, 70);
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 10, 70);

	}
	else if (camscene == 3) {
		App->collisions->AddCollider({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::AIR);	//EL AIRE

		App->collisions->AddCollider({ 0, 247, 352, 18 }, Collider::Type::FLOOR);			//EL SUELO
		App->collisions->AddCollider({ 40, 209, 114, 2 }, Collider::Type::FLOOR);			//BAJO IZQUIERDA
		App->collisions->AddCollider({ 200, 209, 112, 2 }, Collider::Type::FLOOR);			//BAJO DERECHA
		App->collisions->AddCollider({ 0, 171, 154, 2 }, Collider::Type::FLOOR);			//BAJO MEDIO IZQUIERDA
		App->collisions->AddCollider({ 200, 171, 150, 2 }, Collider::Type::FLOOR);			//BAJO MEDIO DERECHA
		App->collisions->AddCollider({ 55, 133, 33, 2 }, Collider::Type::FLOOR);			//MEDIO IZQUIERDA
		App->collisions->AddCollider({ 156, 133, 140, 2 }, Collider::Type::FLOOR);			//MEDIO DERECHA
		App->collisions->AddCollider({ 45, 95, 197, 2 }, Collider::Type::FLOOR);			//MEDIO ALTO
		App->collisions->AddCollider({ 112, 57, 197, 2 }, Collider::Type::FLOOR);			//ALTO

		//Collider de los lados
		App->collisions->AddCollider({ 0, 0, 8, 275 }, Collider::Type::WALL2);				//MURO IZQ
		App->collisions->AddCollider({ 345, 0, 8, 275 }, Collider::Type::WALL);				//MURO DER

		App->collisions->AddCollider({ 40, 190, 4, 19 }, Collider::Type::WALL2);			//MURO IZQUIERDA 1
		App->collisions->AddCollider({ 55, 113, 4, 20 }, Collider::Type::WALL2);			//MURO IZQUIERDA 2
		App->collisions->AddCollider({ 309, 190, 4, 19 }, Collider::Type::WALL);			//MURO DERECHA 1
		App->collisions->AddCollider({ 293, 75, 4, 58 }, Collider::Type::WALL);				//MURO DERECHA 1

		//Deletear la SnowBall
		App->collisions->AddCollider({ 0, 225, 10, 20 }, Collider::Type::DELSNOW);
		App->collisions->AddCollider({ 343, 225, 10, 20 }, Collider::Type::DELSNOW);

		// Enemies ---
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 50, 184);
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 280, 184);
		App->enemies->AddEnemy(ENEMY_TYPE::YELLOWMONKEY, 253, 105);
		App->enemies->AddEnemy(ENEMY_TYPE::YELLOWMONKEY, 110, 67);
		App->enemies->AddEnemy(ENEMY_TYPE::YELLOWMONKEY, 200, 29);

	}
	else if (camscene == 4) {
		App->collisions->AddCollider({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::AIR);	//EL AIRE

		App->collisions->AddCollider({ 0, 247, 352, 18 }, Collider::Type::FLOOR);			//EL SUELO
		App->collisions->AddCollider({ 46, 209, 109, 2 }, Collider::Type::FLOOR);			//BAJO IZQUIERDA
		App->collisions->AddCollider({ 196, 209, 112, 2 }, Collider::Type::FLOOR);			//BAJO DERECHA
		App->collisions->AddCollider({ 0, 171, 88, 2 }, Collider::Type::FLOOR);				//BAJO MEDIO IZQUIERDA
		App->collisions->AddCollider({ 266, 171, 88, 2 }, Collider::Type::FLOOR);			//BAJO MEDIO DERECHA
		App->collisions->AddCollider({ 45, 133, 90, 2 }, Collider::Type::FLOOR);			//MEDIO IZQUIERDA
		App->collisions->AddCollider({ 218, 133, 90, 2 }, Collider::Type::FLOOR);			//MEDIO DERECHA
		App->collisions->AddCollider({ 0, 95, 88, 2 }, Collider::Type::FLOOR);				//ALTO MEDIO IZQUIERDA
		App->collisions->AddCollider({ 266, 95, 88, 2 }, Collider::Type::FLOOR);			//ALTO MEDIO DERECHA
		App->collisions->AddCollider({ 133, 95, 24, 2 }, Collider::Type::FLOOR);			//ALTO MEDIO MEDIO IZQUIERDA
		App->collisions->AddCollider({ 196, 95, 24, 2 }, Collider::Type::FLOOR);			//ALTO MEDIO MEDIO DERECHA
		App->collisions->AddCollider({ 45, 57, 263, 2 }, Collider::Type::FLOOR);			//ALTO

		//Collider de los lados
		App->collisions->AddCollider({ 0, 0, 8, 275 }, Collider::Type::WALL2);				//MURO IZQ
		App->collisions->AddCollider({ 345, 0, 8, 275 }, Collider::Type::WALL);				//MURO DER

		App->collisions->AddCollider({ 154, 76, 4, 20 }, Collider::Type::WALL);				//MURO IZQ 1
		App->collisions->AddCollider({ 154, 190, 4, 20 }, Collider::Type::WALL);			//MURO IZQ 2
		App->collisions->AddCollider({ 132, 97, 4, 37 }, Collider::Type::WALL);				//MURO IZQ 3
		App->collisions->AddCollider({ 194, 76, 4, 20 }, Collider::Type::WALL2);			//MURO DER 1
		App->collisions->AddCollider({ 194, 190, 4, 20 }, Collider::Type::WALL2);			//MURO DER 2
		App->collisions->AddCollider({ 215, 97, 4, 37 }, Collider::Type::WALL2);			//MURO DER 3

		//Deletear la SnowBall
		App->collisions->AddCollider({ 0, 225, 10, 20 }, Collider::Type::DELSNOW);
		App->collisions->AddCollider({ 343, 225, 10, 20 }, Collider::Type::DELSNOW);

		// Enemies ---
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 120, 183);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 205, 183);
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 225, 108);
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 110, 108);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 10, 145);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 315, 145);
		App->enemies->AddEnemy(ENEMY_TYPE::YELLOWMONKEY, 162, 29);

	}
	else if (camscene == 5) {
		App->collisions->AddCollider({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::AIR);	//EL AIRE

		App->collisions->AddCollider({ 0, 247, 352, 18 }, Collider::Type::FLOOR);			//EL SUELO
		App->collisions->AddCollider({ 90, 209, 174, 2 }, Collider::Type::FLOOR);			//BAJO
		App->collisions->AddCollider({ 0, 209, 43, 2 }, Collider::Type::FLOOR);				//BAJO IZQUIERDA
		App->collisions->AddCollider({ 310, 209, 60, 2 }, Collider::Type::FLOOR);			//BAJO DERECHA
		App->collisions->AddCollider({ 0, 171, 43, 2 }, Collider::Type::FLOOR);				//BAJO MEDIO IZQUIERDA
		App->collisions->AddCollider({ 310, 171, 60, 2 }, Collider::Type::FLOOR);			//BAJO MEDIO DERECHA
		App->collisions->AddCollider({ 0, 133, 43, 2 }, Collider::Type::FLOOR);				//MEDIO IZQUIERDA
		App->collisions->AddCollider({ 310, 133, 60, 2 }, Collider::Type::FLOOR);			//MEDIO DERECHA
		App->collisions->AddCollider({ 90, 133, 62, 2 }, Collider::Type::FLOOR);			//MEDIO MEDIO IZQUIERDA
		App->collisions->AddCollider({ 199, 133, 64, 2 }, Collider::Type::FLOOR);			//MEDIO MEDIO DERECHA
		App->collisions->AddCollider({ 0, 95, 88, 2 }, Collider::Type::FLOOR);				//ALTO MEDIO IZQUIERDA
		App->collisions->AddCollider({ 267, 95, 120, 2 }, Collider::Type::FLOOR);			//ALTO MEDIO DERECHA
		App->collisions->AddCollider({ 68, 57, 218, 2 }, Collider::Type::FLOOR);			//ALTO 

		//Collider de los lados
		App->collisions->AddCollider({ 0, 0, 8, 275 }, Collider::Type::WALL2);				//MURO IZQ
		App->collisions->AddCollider({ 151, 134, 4, 30 }, Collider::Type::WALL2);            //MURO IZQ 1
		App->collisions->AddCollider({ 260, 134, 4, 30 }, Collider::Type::WALL2);            //MURO DER 2
		App->collisions->AddCollider({ 198, 134, 4, 30 }, Collider::Type::WALL);            //MURO DER 2
		App->collisions->AddCollider({ 345, 0, 8, 275 }, Collider::Type::WALL);				//MURO DER
		App->collisions->AddCollider({ 88, 134, 4, 30 }, Collider::Type::WALL);            //MURO IZQ 2

		//Deletear la SnowBall
		App->collisions->AddCollider({ 0, 225, 10, 20 }, Collider::Type::DELSNOW);
		App->collisions->AddCollider({ 343, 225, 10, 20 }, Collider::Type::DELSNOW);

		// Enemies ---
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 136, 32);
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 198, 32);
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 225, 108);
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 110, 108);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 10, 145);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 315, 145);
		App->enemies->AddEnemy(ENEMY_TYPE::YELLOWMONKEY, 162, 181);

	}
	else if (camscene == 6) {
		App->collisions->AddCollider({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::AIR);	//EL AIRE

		App->collisions->AddCollider({ 0, 247, 352, 18 }, Collider::Type::FLOOR);			//EL SUELO
		App->collisions->AddCollider({ 64, 209, 90, 2 }, Collider::Type::FLOOR);			//1 IZQUIERDA
		App->collisions->AddCollider({ 200, 209, 90, 2 }, Collider::Type::FLOOR);			//1 DERECHA
		App->collisions->AddCollider({ 0, 190, 65, 2 }, Collider::Type::FLOOR);				//2 IZQUIERDA
		App->collisions->AddCollider({ 288, 190, 90, 2 }, Collider::Type::FLOOR);			//2 DERECHA
		App->collisions->AddCollider({ 130, 171, 67, 2 }, Collider::Type::FLOOR);			//3
		App->collisions->AddCollider({ 85, 152, 45, 2 }, Collider::Type::FLOOR);			//4 IZQUIERDA
		App->collisions->AddCollider({ 284, 152, 80, 2 }, Collider::Type::FLOOR);			//4 DERECHA
		App->collisions->AddCollider({ 45, 133, 41, 2 }, Collider::Type::FLOOR);			//5 IZQUIERDA
		App->collisions->AddCollider({ 178, 133, 107, 2 }, Collider::Type::FLOOR);			//5 DERECHA
		App->collisions->AddCollider({ 68, 95, 87, 2 }, Collider::Type::FLOOR);				//6 IZQUIERDA
		App->collisions->AddCollider({ 266, 95, 106, 2 }, Collider::Type::FLOOR);			//6 DERECHA
		App->collisions->AddCollider({ 155, 76, 67, 2 }, Collider::Type::FLOOR);			//7
		App->collisions->AddCollider({ 0, 57, 109, 2 }, Collider::Type::FLOOR);				//8 IZQUIERDA
		App->collisions->AddCollider({ 222, 57, 86, 2 }, Collider::Type::FLOOR);			//8 DERECHA

		//Collider de los lados
		App->collisions->AddCollider({ 0, 0, 8, 275 }, Collider::Type::WALL2);				//MURO IZQ
		App->collisions->AddCollider({ 345, 0, 8, 275 }, Collider::Type::WALL);				//MURO DER

		App->collisions->AddCollider({ 61, 191, 4, 20 }, Collider::Type::WALL2);			//MURO IZQ 1
		App->collisions->AddCollider({ 126, 153, 4, 20 }, Collider::Type::WALL2);			//MURO IZQ 2
		App->collisions->AddCollider({ 82, 134, 4, 20 }, Collider::Type::WALL2);			//MURO IZQ 3
		App->collisions->AddCollider({ 281, 134, 4, 20 }, Collider::Type::WALL2);			//MURO IZQ 4
		App->collisions->AddCollider({ 288, 191, 4, 20 }, Collider::Type::WALL);			//MURO DER 1
		App->collisions->AddCollider({ 155, 77, 4, 20 }, Collider::Type::WALL);				//MURO DER 2
		App->collisions->AddCollider({ 222, 58, 4, 20 }, Collider::Type::WALL);				//MURO DER 3

		//Deletear la SnowBall
		App->collisions->AddCollider({ 0, 225, 10, 20 }, Collider::Type::DELSNOW);
		App->collisions->AddCollider({ 343, 225, 10, 20 }, Collider::Type::DELSNOW);
		App->collisions->AddCollider({ 343, 133, 10, 20 }, Collider::Type::DELSNOW);        //MURO ESP.

		// Enemies ---
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 50, 31);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 225, 31);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 50, 107);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 300, 164);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 90, 183);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 220, 183);

	}
	else if (camscene == 7) {
		App->collisions->AddCollider({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::AIR);	//EL AIRE

		App->collisions->AddCollider({ 0, 247, 352, 18 }, Collider::Type::FLOOR);			//EL SUELO

		App->collisions->AddCollider({ 90, 209, 174, 2 }, Collider::Type::FLOOR);			//BAJO MEDIO
		App->collisions->AddCollider({ 0, 209, 44, 2 }, Collider::Type::FLOOR);				//BAJO IZQ.
		App->collisions->AddCollider({ 311, 209, 44, 2 }, Collider::Type::FLOOR);			//BAJO DER.
		App->collisions->AddCollider({ 46, 171, 94, 2 }, Collider::Type::FLOOR);			//BAJO MEDIO IZQ.
		App->collisions->AddCollider({ 212, 171, 96, 2 }, Collider::Type::FLOOR);			//BAJO MEDIO DER.
		App->collisions->AddCollider({ 46, 171, 94, 2 }, Collider::Type::FLOOR);			//MEDIO IZQ.
		App->collisions->AddCollider({ 212, 171, 96, 2 }, Collider::Type::FLOOR);			//MEDIO DER.
		App->collisions->AddCollider({ 0, 133, 153, 2 }, Collider::Type::FLOOR);			//ALTO MEDIO IZQ.
		App->collisions->AddCollider({ 200, 133, 153, 2 }, Collider::Type::FLOOR);			//ALTO MEDIO DER.
		App->collisions->AddCollider({ 68, 95, 43, 2 }, Collider::Type::FLOOR);				//ALTO IZQ.
		App->collisions->AddCollider({ 240, 95, 46, 2 }, Collider::Type::FLOOR);			//ALTO DER.
		App->collisions->AddCollider({ 112, 76, 129, 2 }, Collider::Type::FLOOR);			//ALTO 

		//Collider de los lados
		App->collisions->AddCollider({ 0, 0, 8, 275 }, Collider::Type::WALL2);				//MURO IZQ
		App->collisions->AddCollider({ 345, 0, 8, 275 }, Collider::Type::WALL);				//MURO DER

		App->collisions->AddCollider({ 111, 77, 4, 20 }, Collider::Type::WALL);				//MURO IZQ 1
		App->collisions->AddCollider({ 239, 77, 4, 20 }, Collider::Type::WALL2);			//MURO DER 1
		App->collisions->AddCollider({ 139, 152, 4, 21 }, Collider::Type::WALL);			//MURO IZQ 2
		App->collisions->AddCollider({ 210, 152, 4, 21 }, Collider::Type::WALL2);			//MURO DER 2
		App->collisions->AddCollider({ 149, 135, 4, 30 }, Collider::Type::WALL2);			//MURO IZQ 3 
		App->collisions->AddCollider({ 200, 135, 4, 30 }, Collider::Type::WALL);			//MURO DER 3

		//Deletear la SnowBall
		App->collisions->AddCollider({ 0, 225, 10, 20 }, Collider::Type::DELSNOW);
		App->collisions->AddCollider({ 343, 225, 10, 20 }, Collider::Type::DELSNOW);

		// Enemies ---
		App->enemies->AddEnemy(ENEMY_TYPE::YELLOWMONKEY, 160, 48);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 250, 69);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 75, 69);
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 310, 108);
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 30, 108);
		App->enemies->AddEnemy(ENEMY_TYPE::YELLOWMONKEY, 160, 181);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 315, 183);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 10, 183);

	}
	else if (camscene == 8) {
		App->collisions->AddCollider({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::AIR);	//EL AIRE

		App->collisions->AddCollider({ 0, 247, 352, 18 }, Collider::Type::FLOOR);			//EL SUELO
		App->collisions->AddCollider({ 41, 209, 113, 2 }, Collider::Type::FLOOR);			//BAJO IZQ
		App->collisions->AddCollider({ 200, 209, 110, 2 }, Collider::Type::FLOOR);			//BAJO DER
		App->collisions->AddCollider({ 0, 171, 65, 2 }, Collider::Type::FLOOR);				//BAJO MEDIO IZQ
		App->collisions->AddCollider({ 288, 171, 65, 2 }, Collider::Type::FLOOR);			//BAJO MEDIO DER
		App->collisions->AddCollider({ 111, 171, 131, 2 }, Collider::Type::FLOOR);			//BAJO MEDIO MEDIO
		App->collisions->AddCollider({ 41, 133, 113, 2 }, Collider::Type::FLOOR);			//MEDIO IZQ
		App->collisions->AddCollider({ 200, 133, 111, 2 }, Collider::Type::FLOOR);			//MEDIO DER
		App->collisions->AddCollider({ 0, 95, 42, 2 }, Collider::Type::FLOOR);				//ALTO MEDIO IZQ
		App->collisions->AddCollider({ 310, 95, 43, 2 }, Collider::Type::FLOOR);			//ALTO MEDIO DER
		App->collisions->AddCollider({ 129, 95, 93, 2 }, Collider::Type::FLOOR);			//ALTO MEDIO MEDIO
		App->collisions->AddCollider({ 90, 57, 174, 2 }, Collider::Type::FLOOR);			//ALTO

		//Collider de los lados
		App->collisions->AddCollider({ 0, 0, 8, 275 }, Collider::Type::WALL2);				//MURO IZQ
		App->collisions->AddCollider({ 345, 0, 8, 275 }, Collider::Type::WALL);				//MURO DER

		App->collisions->AddCollider({ 40, 190, 4, 20 }, Collider::Type::WALL2);			//MURO IZQ 1
		App->collisions->AddCollider({ 40, 96, 4, 40 }, Collider::Type::WALL2);				//MURO IZQ 2
		App->collisions->AddCollider({ 128, 77, 4, 20 }, Collider::Type::WALL2);			//MURO IZQ 3
		App->collisions->AddCollider({ 309, 190, 4, 20 }, Collider::Type::WALL);			//MURO DER 1
		App->collisions->AddCollider({ 309, 96, 4, 40 }, Collider::Type::WALL);				//MURO DER 2
		App->collisions->AddCollider({ 220, 77, 4, 20 }, Collider::Type::WALL);				//MURO DER 3

		//Deletear la SnowBall
		App->collisions->AddCollider({ 0, 225, 10, 20 }, Collider::Type::DELSNOW);
		App->collisions->AddCollider({ 343, 225, 10, 20 }, Collider::Type::DELSNOW);
		App->collisions->AddCollider({ 130, 77, 4, 20 }, Collider::Type::DELSNOW);

		// Enemies ---
		App->enemies->AddEnemy(ENEMY_TYPE::YELLOWMONKEY, 160, 67);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 270, 183);
		App->enemies->AddEnemy(ENEMY_TYPE::REDDEMON, 55, 183);
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 320, 146);
		App->enemies->AddEnemy(ENEMY_TYPE::SPITFIRE, 20, 146);
		App->enemies->AddEnemy(ENEMY_TYPE::YELLOWMONKEY, 50, 219);

	}
	else if (camscene == 9) {
		App->collisions->AddCollider({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::AIR);	//EL AIRE

		App->collisions->AddCollider({ 0, 247, 352, 18 }, Collider::Type::FLOOR);			//EL SUELO
		App->collisions->AddCollider({ 68, 209, 130, 2 }, Collider::Type::FLOOR);			//BAJO IZQUIERDA
		App->collisions->AddCollider({ 0, 171, 154, 2 }, Collider::Type::FLOOR);			//BAJO MEDIO IZQUIERDA
		App->collisions->AddCollider({ 68, 133, 130, 2 }, Collider::Type::FLOOR);			//MEDIO IZQUIERDA
		App->collisions->AddCollider({ 0, 95, 154, 2 }, Collider::Type::FLOOR);				//ALTO MEDIO IZQUIERDA
		App->collisions->AddCollider({ 245, 152, 154, 2 }, Collider::Type::FLOOR);			//MEDIO/2 DERECHA

		//Collider de los lados
		App->collisions->AddCollider({ 0, 0, 8, 275 }, Collider::Type::WALL2);				//MURO IZQ
		App->collisions->AddCollider({ 345, 0, 8, 275 }, Collider::Type::WALL);				//MURO DER

		//Deletear la SnowBall
		App->collisions->AddCollider({ 0, 225, 10, 20 }, Collider::Type::DELSNOW);
		App->collisions->AddCollider({ 343, 225, 10, 20 }, Collider::Type::DELSNOW);

		// Enemies ---
		App->enemies->AddEnemy(ENEMY_TYPE::BOSS, 250, 170);
	}

	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->points->insert.speed = 0;
	App->points->insert.Reset();
	App->points->coin.speed = 0;
	App->points->coin.Reset();
	
	counter_Text_Disapear = 120;

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	Font = App->fonts->Load("Assets/Fonts_2.png", lookupTable, 2);

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
		xm = (xm / 3) - 11;
		ym = (ym / 3) - 12;
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

	counter_Text_Disapear--;

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

	if (counter_Text_Disapear > 0)
	{
		sprintf_s(Text, 10, "floor %d", camscene + 1);
		App->fonts->BlitText(150, 140, Font, Text);
	}

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
	App->fonts->UnLoad(Font);

	App->enemies->CleanUp();
	App->collisions->CleanUp();
	App->audio->PlayMusic(NULL);

	return true;
}