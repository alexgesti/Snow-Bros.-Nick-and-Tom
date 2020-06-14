#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speedx = 1;
	int speedy = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleRAnim;
	Animation idleLAnim;
	Animation upRAnim;
	Animation upLAnim;
	Animation RAnim;
	Animation LAnim;
	Animation fallRAnim;
	Animation fallLAnim;
	Animation shotRAnim;
	Animation shotLAnim;
	Animation pdead;
	Animation rolling;
	Animation pushingR;
	Animation pushingL;
	Animation kickingR;
	Animation kickingL;

	// Detecta si salta y guarda la posicion inicial para despues calcular cual va a ser la altura del salto
	int ranm = 0;
	bool death = false;
	bool jump = false;
	bool vista = false;
	bool shot = false;
	bool godmode = false;
	bool gravity = true;
	bool idle = false;
	bool boulder = false;
	bool push = false;
	float timerj = 50;
	float timers = 10;
	float high = 0;
	float count = 0;
	float counter_can_use_shoot = 0;
	float counter_can_use_jump = 0;

	int lives = 3;

	// The player's collider
	Collider* colliderf = nullptr;
	Collider* colliderp = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// A countdown to when the player gets destroyed. After a while, the game exits
	int destroyedCountdown = 120;
	int inmortality = 150;

	// Sound effects indices
	uint laserFx = 0;
	uint laserFx2 = 0;
	uint explosionFx = 0;
	// añadí estas dos variables para el sonido
	uint jumpFx = 0;
	uint deathFx = 0;
};

#endif //!__MODULE_PLAYER_H__