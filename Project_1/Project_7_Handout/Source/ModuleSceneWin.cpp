#include "ModuleSceneWin.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleChangeScene.h"
#include "ModuleParticles.h"
#include "ModuleScene.h"
#include "ModuleFonts.h"
#include "ModulePoints.h"

#include "SDL/include/SDL_scancode.h"

ModuleSceneWin::ModuleSceneWin(bool startEnabled) : Module(startEnabled)
{
	name = "Win";

	// Background
	background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// Congrat & Lets Go
	Congrat.PushBack({ 16, 40, 120, 8 });

	LetsGo.PushBack({0, 0, 0, 0});
	LetsGo.PushBack({16, 56, 63, 8});
	LetsGo.loop = false;
}

ModuleSceneWin::~ModuleSceneWin()
{

}

// Load assets
bool ModuleSceneWin::Start()
{
	LOG("Loading background textures");

	bool ret = true;

	Texture = App->textures->Load("Assets/Inicio_Page.png");

	App->particles->CleanUp();

	return ret;
}

update_status ModuleSceneWin::Update()
{
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_DOWN) {
		return update_status::UPDATE_STOP;
	}

	if (count >= 300) count = 0;

	count++;
	LOG("%d", count)

	if (count == 1 * 60) LetsGo.Update();

	if (count == 4 * 60) {
		App->sceneLevel_1->camscene++;
		if (App->sceneLevel_1->camscene == 10) {
			App->change->Changing(this, (Module*)App->sceneIntro, 600);
		}
		App->change->Changing(this, (Module*)App->sceneLevel_1, 60);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneWin::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->DrawQuad(background, 0, 0, 0, 255);

	App->render->Blit(Texture, SCREEN_WIDTH / 2.975f, (SCREEN_HEIGHT / 2.25f) + 5, &(Congrat.GetCurrentFrame()));
	App->render->Blit(Texture, SCREEN_WIDTH / 2.4f, (SCREEN_HEIGHT / 1.95f) + 5, &(LetsGo.GetCurrentFrame()));

	if (App->input->debugGamepadInfo == true) App->input->DebugDrawGamepadInfo();

	return update_status::UPDATE_CONTINUE;
}

void ModuleSceneWin::Reset()
{
	LetsGo.Reset();
}

bool ModuleSceneWin::CleanUp()
{
	Reset();

	App->textures->Unload(Texture);
	App->audio->PlayMusic(NULL);

	return true;
}