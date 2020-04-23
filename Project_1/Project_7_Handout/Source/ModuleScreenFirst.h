#ifndef __MODULE_SCREEN_FIRST_H__
#define __MODULE_SCREEN_FIRST_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleScreenFirst : public Module
{
public:
	//Constructor
	ModuleScreenFirst(bool startEnabled);

	//Destructor
	~ModuleScreenFirst();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	// Disables some textures
	bool CleanUp();


public:
	// The sprite section for the background
	SDL_Rect background; //Cuadrado de fondo negro (un fondo)

	// The title sprite sheet loaded into an SDL_Texture
	SDL_Texture* Texture = nullptr;

	// A set of animations
	Animation Logo;
};

#endif
