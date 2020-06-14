#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "ModuleScene.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModuleChangeScene.h"
#include "ModuleSceneGameOver.h"
#include "ModuleSceneWin.h"
#include "ModuleScreenFirst.h"
#include "ModuleFonts.h"
#include "ModulePoints.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules[0] = window = new ModuleWindow(true);
	modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);

	modules[4] = sceneFirst = new ModuleScreenFirst(true);			//Fisrt scene starts enabled
	modules[5] = sceneIntro = new ModuleSceneIntro(false);			//Intro scene starts disabled
	modules[6] = sceneLevel_1 = new ModuleScene(false);				//Gameplay scene starts disabled
	modules[7] = sceneWin = new ModuleSceneWin(false);				//Win scene starts disabled
	modules[8] = screenGameOver = new ModuleSceneGameOver(false);	//Game Over scene starts disabled
	modules[9] = enemies = new ModuleEnemies(false);				//Enemies start disabled
	modules[10] = player = new ModulePlayer(false);					//Player starts disabled
	modules[11] = particles = new ModuleParticles(true);

	modules[12] = collisions = new ModuleCollisions(false); //Collision starts disabled

	modules[13] = render = new ModuleRender(true);
	modules[14] = change = new ModuleChangeScene(true);

	modules[15] = fonts = new ModuleFonts(true);
	modules[16] = points = new ModulePoints(true);
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	//By now we will consider that all modules are always active
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : update_status::UPDATE_CONTINUE;

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
