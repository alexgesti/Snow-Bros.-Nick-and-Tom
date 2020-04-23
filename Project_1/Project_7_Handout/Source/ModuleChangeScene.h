#ifndef __MODULECHANGESCENE_H_
#define __MODULECHANGESCENE_H_

#include "Module.h"
#include "SDL\include\SDL_rect.h"

class ModuleChangeScene: public Module
{
public:
	//Constructor
	ModuleChangeScene(bool startEnabled);

	//Destructor
	~ModuleChangeScene();

	// Called when the module is activated
	// Enables the blending mode for transparency
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the fade logic
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of a black rectangle with transparency
	update_status PostUpdate() override;

	// Called from another module
	// Starts the fade process which has two steps, fade_out and fade_in
	// After the first step, the modules should be switched
	bool Changing(Module* toDisable, Module* toEnable, float frames = 60);

private:

	enum Fade_Step
	{
		NONE,
		TO_CHANGE,
		CHANGED
	} currentStep = Fade_Step::NONE;

	// A frame count system to handle the fade time and ratio
	Uint32 frameCount = 0;
	Uint32 maxFadeFrames = 0;

	// The modules that should be switched after the first step
	Module* moduleToEnable = nullptr;
	Module* moduleToDisable = nullptr;
};

#endif //__MODULEFADETOBLACK_H__
