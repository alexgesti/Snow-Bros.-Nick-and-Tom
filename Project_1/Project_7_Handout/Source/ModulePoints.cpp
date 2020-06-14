#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePoints.h"
#include "ModuleFonts.h"
#include "ModuleInput.h"

#include <stdio.h>

ModulePoints::ModulePoints(bool isEnabled) : Module(isEnabled)
{
	player1.PushBack({ 0, 0, 16, 9 });
	HI.PushBack({ 19, 0, 14, 9 });
	player2.PushBack({ 36, 0, 19, 9 });

	insert.PushBack({ 0, 11, 63, 9 });
	coin.PushBack({ 66, 11, 42, 9 });
	insert.PushBack({ 0, 0, 0, 0 });
	coin.PushBack({ 0, 0, 0, 0 });
	insert.loop = true;
	coin.loop = true;
	insert.speed = 0.05f;
	coin.speed = 0.05f;

}

ModulePoints::~ModulePoints()
{

}
bool ModulePoints::Start()
{
	bool ret = true;
	texture = App->textures->Load("Assets/HEADER.png");

	char lookupTable[] = { "0123456789" };
	scoreFont = App->fonts->Load("Assets/FontsGame.png", lookupTable, 1);

	return ret;
}
update_status ModulePoints::Update()
{

	if (score > scoreTotal)  scoreTotal = score;

	insert.Update();
	coin.Update();

	return update_status::UPDATE_CONTINUE;
}

void ModulePoints::returnPoints()
{

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);
	sprintf_s(scoreText2, 10, "%7d", scoreTotal);
	App->render->Blit(texture, 4, 5, &(player1.GetCurrentFrame()));
	App->fonts->BlitText(30, 5, scoreFont, scoreText);
	App->render->Blit(texture, 125, 5, &(HI.GetCurrentFrame()));
	App->fonts->BlitText(150, 5, scoreFont, scoreText2);
	App->render->Blit(texture, 245, 5, &(player2.GetCurrentFrame()));
	App->render->Blit(texture, 280, 0, &(insert.GetCurrentFrame()));
	App->render->Blit(texture, 280, 10, &(coin.GetCurrentFrame()));


}
