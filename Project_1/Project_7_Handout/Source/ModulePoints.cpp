#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePoints.h"
#include "ModuleFonts.h"
#include "ModuleInput.h"
#include <stdio.h>

ModulePoints::ModulePoints(bool isEnabled) : Module(isEnabled)
{

}

ModulePoints::~ModulePoints()
{

}
bool ModulePoints::Start()
{
	bool ret = true;
	char lookupTable[] = { "0123456789" };
	scoreFont = App->fonts->Load("Assets/FontsGame.png", lookupTable, 1);

	return ret;
}

void ModulePoints::returnPoints()
{
	
	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);
	App->fonts->BlitText(66, 3, scoreFont, scoreText);
	

}
