#include "ModuleSceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleChangeScene.h"

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
	CoinFx = App->audio->LoadFx("Assets/coin.wav");

	return ret;
}

update_status ModuleSceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && coins >= 1)
	{
		App->change->Changing(this, (Module*)App->sceneLevel_1, 90);
		App->audio->PlayMusic("Assets/start.wav", 0);
		CanStart = true;
	}

	if (App->input->keys[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN)
	{
		coins++;
		Number.Update();
		App->audio->PlayFx(CoinFx);
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

	Title.Update();


	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->DrawQuad(background, 0, 0, 0, 255);

	App->render->Blit(Texture, SCREEN_WIDTH / 5.5f, 25, &(Title.GetCurrentFrame()));
	App->render->DrawQuad(blackScreen, 0, 0, 0, 255);

	App->render->Blit(Texture, PosX, 48, &(Tom.GetCurrentFrame()));
	App->render->Blit(Texture, PosX, 83, &(Nick.GetCurrentFrame()));

	App->render->Blit(Texture2, 121, 190, &(Logo.GetCurrentFrame()));
	App->render->Blit(Texture2, 77, 220, &(Toaplan.GetCurrentFrame()));
	App->render->Blit(Texture2, 92, 235, &(AllRight.GetCurrentFrame()));
	App->render->Blit(Texture2, 145, 250, &(Credit.GetCurrentFrame()));
	App->render->Blit(Texture2, 202, 250, &(Number.GetCurrentFrame()));

	if (CanStart == true)
	{
		App->render->DrawQuad(background2, 0, 0, 0, 255);
		App->render->Blit(Texture2, SCREEN_WIDTH / 2.3f, SCREEN_HEIGHT / 1.95f, &(StartName.GetCurrentFrame()));
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleSceneIntro::Reset()
{
	// Nick&Tom
	PosX = -32;

	//Title
	Title.Reset();
	Title.speed = 0;

	// Coins
	coins = 0;
	Number.Reset();

	// Start
	CanStart = false;
}

bool ModuleSceneIntro::CleanUp()
{
	Reset();

	App->textures->Unload(Texture);
	App->textures->Unload(Texture2);
	CoinFx = NULL;

	return true;
}