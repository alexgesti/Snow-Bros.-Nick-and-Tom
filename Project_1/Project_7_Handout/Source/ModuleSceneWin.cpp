#include "ModuleSceneWin.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleChangeScene.h"

#include "SDL/include/SDL_scancode.h"

ModuleSceneWin::ModuleSceneWin(bool startEnabled) : Module(startEnabled)
{
	// Background
	background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	congrats.PushBack ({ 16, 39, 300, 400 });
	letsgo.PushBack ({ 16, 56, 300, 400 });
	
	}

ModuleSceneWin::~ModuleSceneWin()
{

}

// Load assets
bool ModuleSceneWin::Start()
{
	LOG("Loading background textures");

	bool ret = true;

	Texture = App->textures->Load("Assets/bicho.png");
	
	return ret;
}
update_status ModuleSceneWin::Update()
{
	congrats.Update();
	return update_status::UPDATE_CONTINUE;
}



// Update: draw background
update_status ModuleSceneWin::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->DrawQuad(background, 0, 0, 0, 255);

	App->render->Blit(Texture, SCREEN_WIDTH / 5.5f, 25, &(congrats.GetCurrentFrame()));
	
	return update_status::UPDATE_CONTINUE;
}

void ModuleSceneWin::Reset()
{
	
}

bool ModuleSceneWin::CleanUp()
{
	Reset();

	App->textures->Unload(Texture);
	
	return true;
}