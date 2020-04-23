#include "ModuleScreenFirst.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleChangeScene.h"

#include "SDL/include/SDL_scancode.h"

ModuleScreenFirst::ModuleScreenFirst(bool startEnabled) : Module(startEnabled)
{
	// Background
	background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	Logo.PushBack({ 0, 0, 353, 265});
}

ModuleScreenFirst::~ModuleScreenFirst()
{

}

// Load assets
bool ModuleScreenFirst::Start()
{
	LOG("Loading background textures");

	bool ret = true;

	Texture = App->textures->Load("Assets/Firstpng.png");

	return ret;
}

update_status ModuleScreenFirst::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) App->change->Changing(this, (Module*)App->sceneIntro, 60);

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScreenFirst::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->DrawQuad(background, 0, 0, 0, 255);

	App->render->Blit(Texture, 0, 0, &(Logo.GetCurrentFrame()));


	return update_status::UPDATE_CONTINUE;
}

bool ModuleScreenFirst::CleanUp()
{
	App->textures->Unload(Texture);

	return true;
}
