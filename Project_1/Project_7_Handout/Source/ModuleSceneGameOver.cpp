#include "ModuleSceneGameOver.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleChangeScene.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "ModulePoints.h"

#include "SDL/include/SDL_scancode.h"

ModuleSceneGameOver::ModuleSceneGameOver(bool startEnabled) : Module(startEnabled)
{
	name = "Game Over";

	// Background
	background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// GO
	GO.PushBack({1, 1, 228, 29});

	// Bolas
	for (int i = 0; i <= 7; i++)
	{
		Bola_1[i].PushBack({ 3, 34, 42, 45 });
		Bola_1[i].PushBack({ 51, 34, 42, 45 });
		Bola_1[i].PushBack({ 99, 34, 42, 45 });
		Bola_1[i].PushBack({ 147, 34, 42, 45 });
		Bola_1[i].PushBack({ 0, 0, 0, 0 });
		Bola_1[i].loop = false;
		Bola_1[i].speed = 0.35f;
	}

	// Enemies
	E_1.PushBack({2, 83, 27, 27});
	E_1.PushBack({35, 83, 27, 27});
	E_1.speed = 0.15f;

	E_2.PushBack({66, 82, 29, 28});
	E_2.PushBack({99, 82, 29, 28});
	E_2.speed = 0.15f;

	E_3.PushBack({131, 84, 28, 26});
	E_3.PushBack({162, 84, 28, 26});
	E_3.speed = 0.15f;

	E_4.PushBack({198, 84, 22, 26});
	E_4.PushBack({229, 84, 22, 26});
	E_4.speed = 0.15f;
}

ModuleSceneGameOver::~ModuleSceneGameOver()
{

}

// Load assets
bool ModuleSceneGameOver::Start()
{
	LOG("Loading background textures");

	bool ret = true;

	Texture = App->textures->Load("Assets/GameOver.png");
	Laugh = App->audio->LoadFx("Assets/Laugh.wav");

	App->audio->PlayMusic("Assets/Game Over_2.ogg", 0);

	for (int k = 1; k <= 7; k++) Bola_1[k].speed = 0;

	return ret;
}

update_status ModuleSceneGameOver::Update()
{
	for (int j = 0; j <= 7; j++)
	{
		Bola_1[j].Update();
		if (Bola_1[j].FinishedAlready && j != 7) Bola_1[j + 1].speed = 0.35f;
		if (Bola_1[7].FinishedAlready) EnemieNow = true;
	}
	
	if (EnemieNow)
	{
		E_1.Update();
		E_2.Update();
		E_3.Update();
		E_4.Update();
		if (OneTime)
		{
			App->audio->PlayFx(Laugh);
			OneTime = false;
		}
	}

	count++;

	if (count == 4 * 60)
	{
		App->audio->PlayMusic(NULL, 0);
		App->change->Changing(this, (Module*)App->sceneIntro, 60);
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_DOWN) {
		return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneGameOver::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->DrawQuad(background, 0, 0, 0, 255);

	App->render->Blit(Texture, SCREEN_WIDTH / 5.5f, SCREEN_HEIGHT / 3, &(GO.GetCurrentFrame()));
	App->render->Blit(Texture, SCREEN_WIDTH / 1.375f, SCREEN_HEIGHT / 3.25f, &(Bola_1[7].GetCurrentFrame()));
	App->render->Blit(Texture, SCREEN_WIDTH / 1.55f, SCREEN_HEIGHT / 3.25f, &(Bola_1[6].GetCurrentFrame()));
	App->render->Blit(Texture, SCREEN_WIDTH / 1.75f, SCREEN_HEIGHT / 3.25f, &(Bola_1[5].GetCurrentFrame()));
	App->render->Blit(Texture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3.25f, &(Bola_1[4].GetCurrentFrame()));
	App->render->Blit(Texture, SCREEN_WIDTH / 2.5f, SCREEN_HEIGHT / 3.25f, &(Bola_1[3].GetCurrentFrame()));
	App->render->Blit(Texture, SCREEN_WIDTH / 3.1f, SCREEN_HEIGHT / 3.25f, &(Bola_1[2].GetCurrentFrame()));
	App->render->Blit(Texture, SCREEN_WIDTH / 4.25f, SCREEN_HEIGHT / 3.25f, &(Bola_1[1].GetCurrentFrame()));
	App->render->Blit(Texture, SCREEN_WIDTH / 6.25f, SCREEN_HEIGHT / 3.25f, &(Bola_1[0].GetCurrentFrame()));

	if (EnemieNow)
	{
		App->render->Blit(Texture, SCREEN_WIDTH / 3.75f, SCREEN_HEIGHT / 1.75f, &(E_1.GetCurrentFrame()));
		App->render->Blit(Texture, SCREEN_WIDTH / 2.45f, (SCREEN_HEIGHT / 1.75f) - 1, &(E_2.GetCurrentFrame()));
		App->render->Blit(Texture, SCREEN_WIDTH / 1.8f, (SCREEN_HEIGHT / 1.75f) + 1, &(E_3.GetCurrentFrame()));
		App->render->Blit(Texture, SCREEN_WIDTH / 1.42f, SCREEN_HEIGHT / 1.75f, &(E_4.GetCurrentFrame()));
	}

	if (App->input->debugGamepadInfo == true) App->input->DebugDrawGamepadInfo();

	return update_status::UPDATE_CONTINUE;
}

void ModuleSceneGameOver::Reset()
{
	for (int a = 1; a <= 7; a++)
	{
		Bola_1[a].Reset();
		Bola_1[a].FinishedAlready = false;
	}

	E_1.Reset();
	E_2.Reset();
	E_3.Reset();
	E_4.Reset();

	//Enemie activate
	EnemieNow = false;

	// Enemies Laugh
	Laugh = 0;
	OneTime = true;

	count = 0;
}

bool ModuleSceneGameOver::CleanUp()
{
	Reset();

	App->textures->Unload(Texture);
	App->audio->UnloadFx(Laugh);

	App->audio->PlayMusic(NULL);

	return true;
}