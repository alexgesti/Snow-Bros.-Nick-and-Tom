#include "ModuleChangeScene.h"

#include "Application.h"
#include "ModuleRender.h"

#include "SDL/include/SDL_render.h"

ModuleChangeScene::ModuleChangeScene(bool startEnabled) : Module(startEnabled)
{

}

ModuleChangeScene::~ModuleChangeScene()
{

}

bool ModuleChangeScene::Start()
{
	return true;
}

update_status ModuleChangeScene::Update()
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE)
	{
		return update_status::UPDATE_CONTINUE;
	}

	if (currentStep == Fade_Step::TO_CHANGE)
	{
		++frameCount;
		if (frameCount >= maxFadeFrames)
		{
			moduleToDisable->Disable();
			moduleToEnable->Enable();

			currentStep = Fade_Step::CHANGED;
		}
	}
	else
	{
		--frameCount;
		if (frameCount <= 0)
		{
			currentStep = Fade_Step::NONE;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleChangeScene::PostUpdate()
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return update_status::UPDATE_CONTINUE;

	float fadeRatio = (float)frameCount / (float)maxFadeFrames;

	return update_status::UPDATE_CONTINUE;
}

bool ModuleChangeScene::Changing(Module* moduleToDisable, Module* moduleToEnable, float frames)
{
	bool ret = false;

	// If we are already in a fade process, ignore this call
	if (currentStep == Fade_Step::NONE)
	{
		currentStep = Fade_Step::TO_CHANGE;
		frameCount = 0;
		maxFadeFrames = frames;

		this->moduleToDisable = moduleToDisable;
		this->moduleToEnable = moduleToEnable;

		ret = true;
	}

	return ret;
}