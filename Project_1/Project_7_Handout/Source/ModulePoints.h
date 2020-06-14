#ifndef __MODULE_POINTS_H__
#define __MODULE_POINTS_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModulePoints : public Module
{
public:
	ModulePoints(bool startEnabled);

	//Destructor
	~ModulePoints();
	bool Start() override;
	void returnPoints();
	update_status Update();

	//Fonts 
	int score = 000;
	int scoreTotal = 40000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };
	char scoreText2[10] = { "\0" };


	SDL_Texture* texture = nullptr;
	Animation* currentAnimation = nullptr;

	Animation player1;
	Animation HI;
	Animation player2;
	Animation insert;
	Animation coin;

};
#endif // __ModulePoints_H