#ifndef __MODULE_SCENE_INTRO_H__
#define __MODULE_SCENE_INTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleSceneIntro : public Module
{
public:
	//Constructor
	ModuleSceneIntro(bool startEnabled);

	//Destructor
	~ModuleSceneIntro();

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

	// Resets All Stats
	void Reset();

public:
	// The sprite section for the background
	SDL_Rect background;
	SDL_Rect background2;
	SDL_Rect blackScreen;

	// The title sprite sheet loaded into an SDL_Texture
	SDL_Texture* Texture = nullptr;
	SDL_Texture* Texture2 = nullptr;
	SDL_Texture* TextureSnowBros = nullptr;
	SDL_Texture* TextureDemon = nullptr;

	// A set of animations
	Animation Nick;
	Animation Tom;
	Animation Title;
	Animation Logo;
	Animation Toaplan;
	Animation AllRight;
	Animation Credit;
	Animation Number;
	Animation StartName;

	Animation TitleColor;

	Animation Aparece;
	Animation Particles;
	Animation CurrentAnim;
	Animation idleRAnim;
	Animation idleLAnim;
	Animation upAnim;
	Animation RAnim;
	Animation LAnim;
	Animation fallAnim;
	Animation shotAnim;

	Animation CurrentAnim2;
	Animation walkAnim;
	Animation dead1;
	Animation dead2;
	Animation dead3;
	Animation dead4;
	Animation bolaMove;
	
	Animation Whattodo;

	// Nick&Tom positions
	int PosX = -32;
	int PosXIntro = 162;
	int PosYIntro = 216;

	// Red demon position
	int PosXDemon = SCREEN_WIDTH;
	int PosYDemon = 215;

	// Coins and Sound
	int coins = 0;
	int CoinFx = 0;
	int ApareceFx = 0;
	int JumpFx = 0;
	int ShootFx = 0;
	int ThrowFx = 0;
	int CollFx = 0;

	// Timer
	float Timer_Second_part;
	float Timer_Loop;
	float Timer_Kill_Enemy;
	float Timer_ShotStart;

	// Counters
	int count_Ini = 0;
	float counter_put_money = 0;

	// Bools
	bool Jumped;
	bool EnemyAproaching;
	
	// Start
	bool CanStart = false;
};

#endif
