#include "ModuleSceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleChangeScene.h"
#include "ModuleScene.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include "ModulePoints.h"

#include "SDL/include/SDL_scancode.h"

ModuleSceneIntro::ModuleSceneIntro(bool startEnabled) : Module(startEnabled)
{
	// Background
	background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	background2 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// BlackScreen
	blackScreen = { PosX, 25, 350, 111 };

	// Nick & Tom
	Nick.PushBack({ 16, 123, 32, 53 });
	Nick.PushBack({ 64, 123, 32, 53 });
	Nick.PushBack({ 112, 123, 32, 53 });
	Nick.PushBack({ 160, 123, 32, 53 });
	Nick.speed = 0.125f;

	Tom.PushBack({ 224, 123, 32, 53 });
	Tom.PushBack({ 272, 123, 32, 53 });
	Tom.PushBack({ 320, 123, 32, 53 });
	Tom.PushBack({ 368, 123, 32, 53 });
	Tom.speed = 0.125f;

	// Title
	Title.PushBack({ 16, 1, 229, 111 });
	Title.PushBack({ 266, 1, 229, 111 });
	Title.PushBack({ 516, 1, 229, 111 });
	Title.PushBack({ 765, 1, 229, 111 });
	Title.PushBack({ 1016, 1, 229, 111 });
	Title.loop = false;
	Title.speed = 0;

	TitleColor.PushBack({ 1248, 1, 229, 111 });

	// Toaplan Rights
	Logo.PushBack({53, 2, 108, 20});
	Toaplan.PushBack({9, 27, 196, 8});
	AllRight.PushBack({23, 39, 162, 8});
	Credit.PushBack({1, 51, 48, 8});

	// Credits Numbers
	Number.PushBack({ 1, 63, 8, 8}); // 0
	Number.PushBack({ 9, 63, 8, 8 });// 1
	Number.PushBack({ 16, 63, 8, 8 });// 2
	Number.PushBack({ 25, 63, 8, 8 });// 3
	Number.PushBack({ 33, 63, 8, 8 });// 4
	Number.PushBack({ 42, 63, 8, 8 });// 5
	Number.PushBack({ 50, 63, 8, 8 });// 6
	Number.PushBack({ 59, 63, 8, 8 });// 7
	Number.PushBack({ 67, 63, 8, 8 });// 8
	Number.PushBack({ 76, 63, 8, 8 });// 9
	Number.loop = false;

	// Start
	StartName.PushBack({53, 51, 42, 8});

	//Nick Intro_2
	Aparece.PushBack({ 0, 608, 48, 46 });
	Aparece.PushBack({ 48, 608, 48, 46 });
	Aparece.PushBack({ 96, 608, 48, 46 });
	Aparece.PushBack({ 144, 608, 48, 46 });
	Aparece.PushBack({ 192, 608, 48, 46 });
	Aparece.PushBack({ 256, 608, 48, 46 });
	Aparece.PushBack({ 320, 608, 48, 46 });
	Aparece.PushBack({ 384, 608, 48, 46 });
	Aparece.PushBack({ 0, 0, 0, 0 });
	Aparece.loop = false;
	Aparece.speed = 0.25f;
	
	// idle animation - just one sprite
	idleRAnim.PushBack({ 16, 16, 21, 27 });
	idleLAnim.PushBack({ 283, 75, 21, 27 });

	fallAnim.PushBack({ 345 , 131, 20, 30 });

	// Move vertical
	upAnim.PushBack({ 546, 131, 20, 30 });
	upAnim.PushBack({ 516, 134, 22, 27 });
	upAnim.PushBack({ 488, 138, 20, 23 });
	upAnim.PushBack({ 460, 139, 20, 22 });
	upAnim.PushBack({ 432, 134, 20, 27 });
	upAnim.PushBack({ 404, 137, 20, 24 });
	upAnim.PushBack({ 373, 138, 23, 23 });
	upAnim.PushBack({ 345, 131, 20, 30 });
	upAnim.loop = false;
	upAnim.speed = 0.15f;

	// Move Horizontal
	RAnim.PushBack({ 16, 52, 18, 28 });
	RAnim.PushBack({ 48, 53, 16, 27 });
	RAnim.PushBack({ 80, 52 , 19, 28 });
	RAnim.PushBack({ 112, 53, 16, 27 });
	RAnim.loop = true;
	RAnim.speed = 0.1f;

	LAnim.PushBack({ 16, 100, 19, 28 });
	LAnim.PushBack({ 45, 101, 19, 27 });
	LAnim.PushBack({ 79, 100, 20, 28 });
	LAnim.PushBack({ 109 , 101, 19, 27 });
	LAnim.loop = true;
	LAnim.speed = 0.1f;

	Particles.PushBack({ 441, 623, 26, 31 }); 
	Particles.PushBack({ 482, 623, 26, 31 });
	Particles.PushBack({ 523, 623, 26, 31 });
	Particles.PushBack({ 564, 623, 26, 31 });
	Particles.loop = true;
	Particles.speed = 0.25f;

	shotAnim.PushBack({ 141, 78, 21, 26 });
	shotAnim.PushBack({ 170, 75, 20, 29 });
	shotAnim.PushBack({ 198, 77, 27, 27 });
	shotAnim.PushBack({ 233, 77, 27, 27 });
	shotAnim.loop = true;
	shotAnim.speed = 0.25f;

	//Red demon
	walkAnim.PushBack({ 111, 6, 29, 28 });
	walkAnim.PushBack({ 79, 6, 30, 28 });
	walkAnim.PushBack({ 47, 7, 29, 27 });
	walkAnim.speed = 0.1f;
	walkAnim.loop = true;

	dead1.PushBack({ 15, 41, 28, 26 });
	dead1.PushBack({ 47, 39, 28, 30 });
	dead1.speed = 0.1f;
	dead1.loop = true;

	dead2.PushBack({ 46, 234, 28, 30 });
	dead2.PushBack({ 78, 234, 28, 30 });
	dead2.speed = 0.1f;
	dead2.loop = true;

	dead3.PushBack({ 46, 272, 28, 30 });
	dead3.PushBack({ 78, 272, 28, 30 });
	dead3.speed = 0.1f;
	dead3.loop = true;

	dead4.PushBack({ 46, 313, 28, 30 });
	dead4.PushBack({ 78, 313, 28, 30 });
	dead4.speed = 0.1f;
	dead4.loop = true;

	bolaMove.PushBack({ 199, 703, 26, 31});
	bolaMove.PushBack({ 232, 703, 26, 31 });
	bolaMove.PushBack({ 266, 703, 26, 31 });
	bolaMove.PushBack({ 299, 703, 26, 31 });
	bolaMove.speed = 0.25f;
	bolaMove.loop = true;

	Whattodo.PushBack({0, 128, 208, 48 });
	Whattodo.PushBack({208, 80, 208, 48 });
	Whattodo.PushBack({208, 128, 208, 48 });
	Whattodo.loop = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{
	
}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading background textures");

	bool ret = true;

	Texture = App->textures->Load("Assets/Title_1.png");
	Texture2 = App->textures->Load("Assets/Title_ToplanRights.png");
	TextureSnowBros = App->textures->Load("Assets/Nick&Tom.png");
	TextureDemon = App->textures->Load("Assets/demonio.png");
	CoinFx = App->audio->LoadFx("Assets/coin.wav");
	ApareceFx = App->audio->LoadFx("Assets/Aparicion.wav");
	JumpFx = App->audio->LoadFx("Assets/jump.wav");
	ShootFx = App->audio->LoadFx("Assets/shot.wav");
	ThrowFx = App->audio->LoadFx("Assets/throw.wav");
	CollFx = App->audio->LoadFx("Assets/collision.wav");

	coins = 0;
	CanStart = false;

	Timer_Second_part = 0;
	Timer_Loop = 0;
	Timer_Kill_Enemy = 0;
	Timer_ShotStart = 0;

	count_Ini = 0;

	Jumped = false;
	EnemyAproaching = false;

	App->sceneLevel_1->camscene = 0;
	App->player->lives = 3;
	App->points->score = 0;
	App->points->insert.speed = 0.05f;
	App->points->coin.speed = 0.05f;

	return ret;
}

update_status ModuleSceneIntro::Update()
{
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT && coins >= 1 ||
		pad.start && coins >= 1)
	{
		App->change->Changing(this, (Module*)App->sceneLevel_1, 60);
		if (CanStart == false) App->audio->PlayMusic("Assets/start.wav", 0);
		CanStart = true;
	}

	if (App->input->keys[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN || pad.b)
	{
		if (counter_put_money == 0)
		{
			coins++;
			counter_put_money = 5;
			Number.Update();
			if (coins <= 9) App->audio->PlayFx(CoinFx);
		}
	}

	if (counter_put_money != 0)
	{
		if (pad.b) counter_put_money = 5;
		pad.b = false;

		counter_put_money--;
	}


	if (PosX < SCREEN_WIDTH && CanStart == false)
	{
		PosX++;
		Nick.Update();
		Tom.Update();

		blackScreen.x = PosX + 11;
	}
	else
	{
		Title.speed = 0.15f;
	}

	if (Title.FinishedAlready)
	{
		if (Timer_Second_part == 1800) App->audio->PlayFx(ApareceFx);
		Timer_Second_part++;
	}

	if (Aparece.FinishedAlready && count_Ini != 7)
	{
		Timer_Loop++;

		if (Timer_Loop > 30)
		{
			Timer_Loop = 0;
			count_Ini++;
		}
	}

	if (Timer_Second_part > 1800 && Aparece.FinishedAlready == false)
	{
		Aparece.Update();
		CurrentAnim = idleRAnim;
	}
	else Particles.Update();
	
	if (count_Ini == 7)
	{
		if (PosXIntro > 62 && EnemyAproaching == false && PosYIntro > 186)
		{
			PosXIntro--;

			CurrentAnim = LAnim;
			LAnim.Update();
		}
		else
		{
			CurrentAnim = idleRAnim;
		}

		if (PosYIntro > 186 && PosXIntro <= 167 && Jumped == false)
		{
			PosYIntro--;

			CurrentAnim = upAnim;
			upAnim.Update();
		}
		else if (Jumped == false && PosYIntro <= 186) Jumped = true;
		else if (PosYIntro < 216 && Jumped && EnemyAproaching == false)
		{
			PosYIntro++;

			CurrentAnim = fallAnim;
		}

		if (PosXDemon > 173 && Jumped && Timer_Kill_Enemy == 0)
		{
			PosXDemon--;

			CurrentAnim2 = walkAnim;
			walkAnim.Update();
		}
			
		if (PosXDemon <= 252) EnemyAproaching = true;

		if (EnemyAproaching && PosXIntro < 142 && Timer_Kill_Enemy < 340)
		{
			PosXIntro++;

			CurrentAnim = RAnim;
			RAnim.Update();
		}
		else if (EnemyAproaching && PosXIntro >= 142 && Timer_Kill_Enemy < 360)
		{
			Timer_Kill_Enemy++;

			CurrentAnim = shotAnim;
			shotAnim.Update();
			Timer_ShotStart++;
		}
		
		if (Timer_ShotStart > 14)  Timer_ShotStart = 0;

		if (Timer_Kill_Enemy >= 1 && Timer_Kill_Enemy <= 90)
		{
			CurrentAnim2 = dead1;
			dead1.Update();
		}
		else if (Timer_Kill_Enemy >= 90 && Timer_Kill_Enemy <= 150)
		{
			CurrentAnim2 = dead2;
			dead2.Update();
		}
		else if (Timer_Kill_Enemy >= 150 && Timer_Kill_Enemy <= 210)
		{
			CurrentAnim2 = dead3;
			dead3.Update();
		}
		else if (Timer_Kill_Enemy >= 210 && Timer_Kill_Enemy <= 270)
		{
			CurrentAnim2 = dead4;
			dead4.Update();
		}
		else if (Timer_Kill_Enemy >= 270 && Timer_Kill_Enemy <= 300)
		{
			CurrentAnim2 = bolaMove;
		}
		else if (Timer_Kill_Enemy >= 300 && Timer_Kill_Enemy <= 340)
		{
			CurrentAnim = idleRAnim;

			bolaMove.Update();

			PosXDemon += 5;
		}
		else if (Timer_Kill_Enemy >= 340 && PosXIntro > -50)
		{
			PosXIntro--;

			CurrentAnim = LAnim;
			LAnim.Update();
		}

		if (PosYIntro == 215 && PosXIntro <= 167 && Jumped == false) App->audio->PlayFx(JumpFx);
		
		if (Timer_ShotStart == 1 && Timer_Kill_Enemy <= 300) App->audio->PlayFx(ShootFx);

		if (Timer_Kill_Enemy == 274) App->audio->PlayFx(ThrowFx);

		if (PosXDemon >= SCREEN_WIDTH && Timer_Kill_Enemy == 339) App->audio->PlayFx(CollFx);

		if (PosXDemon == 252 || Timer_Kill_Enemy == 175) Whattodo.Update();

	}

	Title.Update();

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_DOWN) {
		return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->DrawQuad(background, 0, 0, 0, 255);

	if (Timer_Second_part < 1800) App->render->Blit(Texture, SCREEN_WIDTH / 5.5f, 25, &(Title.GetCurrentFrame()));
	else
	{
		App->render->Blit(Texture, 50, 25, &(TitleColor.GetCurrentFrame()));
		App->render->Blit(Texture2, 75, 145, &(Whattodo.GetCurrentFrame()));
	}
	App->render->DrawQuad(blackScreen, 0, 0, 0, 255);

	App->render->Blit(Texture, PosX, 48, &(Tom.GetCurrentFrame()));
	App->render->Blit(Texture, PosX, 83, &(Nick.GetCurrentFrame()));

	if (Timer_Second_part < 1800) 
	{
		App->render->Blit(Texture2, 121, 190, &(Logo.GetCurrentFrame()));
		App->render->Blit(Texture2, 77, 220, &(Toaplan.GetCurrentFrame()));
		App->render->Blit(Texture2, 92, 235, &(AllRight.GetCurrentFrame()));
	}
	else
	{
		App->render->Blit(TextureSnowBros, (SCREEN_WIDTH / 2.35f), (SCREEN_HEIGHT / 1.345f), &(Aparece.GetCurrentFrame()));
	}

	if (Aparece.FinishedAlready)
	{
		if (count_Ini < 2) if (Timer_Loop < 15) App->render->Blit(TextureSnowBros, (SCREEN_WIDTH / 2.2f), (SCREEN_HEIGHT / 1.25f), &(Particles.GetCurrentFrame()));
	
		if (count_Ini < 5) if (Timer_Loop > 15 && Timer_Loop < 30) App->render->Blit(TextureSnowBros, PosXIntro, PosYIntro, &(CurrentAnim.GetCurrentFrame()));
	}

	if (count_Ini > 5)
	{
		App->render->Blit(TextureSnowBros, PosXIntro, PosYIntro, &(CurrentAnim.GetCurrentFrame()));

		if (Timer_Kill_Enemy <= 270) App->render->Blit(TextureDemon, PosXDemon, PosYDemon, &(CurrentAnim2.GetCurrentFrame()));
		else App->render->Blit(TextureSnowBros, PosXDemon, PosYDemon, &(CurrentAnim2.GetCurrentFrame()));
	}

	App->render->Blit(Texture2, 145, 250, &(Credit.GetCurrentFrame()));
	App->render->Blit(Texture2, 202, 250, &(Number.GetCurrentFrame()));

	if (CanStart == true)
	{
		App->render->DrawQuad(background2, 0, 0, 0, 255);
		App->render->Blit(Texture2, SCREEN_WIDTH / 2.3f, SCREEN_HEIGHT / 1.95f, &(StartName.GetCurrentFrame()));
	}

	App->points->returnPoints();

	if (App->input->debugGamepadInfo == true) App->input->DebugDrawGamepadInfo();

	return update_status::UPDATE_CONTINUE;
}

void ModuleSceneIntro::Reset()
{
	// Nick&Tom positions
	PosX = -32;
	PosXIntro = 162;
	PosYIntro = 216;

	// Demon positions
	PosXDemon = SCREEN_WIDTH;
	PosYDemon = 215;
	
	//Floats
	Title.speed = 0;
	coins = 0;
	
	//Timers
	Timer_Second_part = 0;
	Timer_Loop = 0;
	Timer_Kill_Enemy = 0;
	Timer_ShotStart = 0;

	count_Ini = 0;

	//Bools
	CanStart = false;
	Jumped = false;
	EnemyAproaching = false;

	//Anims Reset
	Title.Reset();
	Number.Reset();

	Aparece.Reset();
	Particles.Reset();
	upAnim.Reset();

	bolaMove.Reset();

	Whattodo.Reset();
}

bool ModuleSceneIntro::CleanUp()
{
	Reset();

	App->textures->Unload(Texture);
	App->textures->Unload(Texture2);
	CoinFx = NULL;

	return true;
}