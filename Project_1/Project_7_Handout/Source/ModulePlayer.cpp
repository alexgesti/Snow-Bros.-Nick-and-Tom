#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleChangeScene.h"
#include "ModuleEnemies.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleRAnim.PushBack({ 16, 16, 21, 27 });
	idleLAnim.PushBack({ 283, 75, 21, 27 });

	fallRAnim.PushBack({ 16, 304, 20, 30 });
	fallLAnim.PushBack({ 345 , 131, 20, 30 });

	// Move vertical
	upRAnim.PushBack({ 16, 304, 20, 30 });
	upRAnim.PushBack({ 44, 307, 22, 27 });
	upRAnim.PushBack({ 74, 311, 20, 23 });
	upRAnim.PushBack({ 102, 312, 20, 22 });
	upRAnim.PushBack({ 130, 307, 20, 27 });
	upRAnim.PushBack({ 158, 310, 20, 24 });
	upRAnim.PushBack({ 186, 311, 23, 23 });
	upRAnim.PushBack({ 217, 304, 20, 30 });
	upRAnim.loop = false;
	upRAnim.speed = 0.15f;

	upLAnim.PushBack({ 546, 131, 20, 30 });
	upLAnim.PushBack({ 516, 134, 22, 27 });
	upLAnim.PushBack({ 488, 138, 20, 23 });
	upLAnim.PushBack({ 460, 139, 20, 22 });
	upLAnim.PushBack({ 432, 134, 20, 27 });
	upLAnim.PushBack({ 404, 137, 20, 24 });
	upLAnim.PushBack({ 373, 138, 23, 23 });
	upLAnim.PushBack({ 345, 131, 20, 30 });
	upLAnim.loop = false;
	upLAnim.speed = 0.15f;

	// Move Horizontal
	RAnim.PushBack({ 16, 52, 18, 28 });
	RAnim.PushBack({ 48, 53, 16, 27 });
	RAnim.PushBack({ 80, 52 , 19, 28 });
	RAnim.PushBack({ 112, 53, 16, 27 });
	RAnim.loop = true;
	RAnim.speed = 0.1f;

	LAnim.PushBack({ 16, 100, 19, 28 });
	LAnim.PushBack({ 45, 101, 19, 27 });
	LAnim.PushBack({ 79, 100, 20, 28 });
	LAnim.PushBack({ 109 , 101, 19, 27 });
	LAnim.loop = true;
	LAnim.speed = 0.1f;

	shotRAnim.PushBack({ 141, 78, 21, 26 });
	shotRAnim.PushBack({ 170, 75, 20, 29 });
	shotRAnim.PushBack({ 198, 77, 27, 27 });
	shotRAnim.PushBack({ 233, 77, 27, 27 });
	shotRAnim.loop = false;
	shotRAnim.speed = 0.5f;

	shotLAnim.PushBack({ 420, 81, 21, 26 });
	shotLAnim.PushBack({ 392, 78, 20, 29 });
	shotLAnim.PushBack({ 357, 80, 27, 27 });
	shotLAnim.PushBack({ 322, 80, 27, 27 });
	shotLAnim.loop = false;
	shotLAnim.speed = 0.5f;

	pdead.PushBack({ 16, 531, 30, 29 });
	pdead.PushBack({ 54, 528, 29, 32 });
	pdead.PushBack({ 91, 531, 30, 29 });
	pdead.PushBack({ 54, 528, 29, 32 });
	pdead.PushBack({ 91, 531, 30, 29 });
	pdead.PushBack({ 54, 528, 29, 32 });
	pdead.PushBack({ 91, 531, 30, 29 });
	pdead.PushBack({ 54, 528, 29, 32 });
	pdead.PushBack({ 91, 531, 30, 29 });
	pdead.PushBack({ 54, 528, 29, 32 });
	pdead.PushBack({ 91, 531, 30, 29 });
	pdead.PushBack({ 129, 535, 28, 25 });
	pdead.PushBack({ 165, 539, 30, 22 });
	pdead.PushBack({ 203, 544, 32, 16 });
	pdead.PushBack({ 243, 547, 32, 13 });
	pdead.PushBack({ 283, 552, 32, 8 });
	pdead.PushBack({ 1, 1, 1, 1 });
	pdead.loop = false;
	pdead.speed = 0.3f;

	rolling.PushBack({16, 378, 22, 21});
	rolling.PushBack({ 46, 373, 20, 25 });
	rolling.loop = true;
	rolling.speed = 0.2f;

	pushingR.PushBack({ 16, 185, 20, 28});
	pushingR.PushBack({ 44, 186, 21, 27 });
	pushingR.PushBack({ 73, 185, 20, 28 });
	pushingR.PushBack({ 101, 186, 20, 27 });
	pushingR.loop = true;
	pushingR.speed = 0.1f;

	pushingL.PushBack({ 565, 231, 20, 28 });
	pushingL.PushBack({ 536, 232, 21, 27 });
	pushingL.PushBack({ 508, 231, 20, 28 });
	pushingL.PushBack({ 480, 232, 20, 28 });
	pushingL.loop = true;
	pushingL.speed = 0.1f;

	kickingR.PushBack({ 153, 185, 22, 28 });
	kickingR.PushBack({ 183, 186, 16, 27 });
	kickingR.PushBack({ 209, 184, 25, 29 });
	kickingR.PushBack({ 242, 184, 25, 29 });
	kickingR.loop = true;
	kickingR.speed = 0.1f;

	kickingL.PushBack({ 426, 231, 22, 28 });
	kickingL.PushBack({ 400, 232, 18, 27 });
	kickingL.PushBack({ 367, 230, 25, 29 });
	kickingL.PushBack({ 334, 230, 25, 29 });
	kickingL.loop = true;
	kickingL.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Nick&Tom.png");
	currentAnimation = &idleRAnim;

	laserFx = App->audio->LoadFx("Assets/shot.wav");
	jumpFx = App->audio->LoadFx("Assets/jump.wav");
	deathFx = App->audio->LoadFx("Assets/death.wav");

	position.x = 150;
	position.y = 221;

	colliderf = App->collisions->AddCollider({ position.x, position.y, 17, 3 }, Collider::Type::FEET, this);
	colliderp = App->collisions->AddCollider({ position.x, position.y, 21, 25 }, Collider::Type::PLAYER, this);

	lives = 3;		//Reinicia CUANDO SE CAMBIA DE ESCENA. WATCH OUT!!
	jump = false;

	return ret;
}

update_status ModulePlayer::Update()
{
	if (death == false) {
		//Gravedad
		if (gravity == true && jump == false)
		{
			position.y += speedy;
			if (vista == 1) {
				if (currentAnimation != &fallLAnim)
				{
					fallLAnim.Reset();
					currentAnimation = &fallLAnim;
				}
			}
			else {
				if (currentAnimation != &fallRAnim)
				{
					fallRAnim.Reset();
					currentAnimation = &fallRAnim;
				}
			}
		}

		if (boulder == false) {
			if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT
				&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
			{
				position.x -= speedx;
				vista = true;
				if (currentAnimation != &LAnim && shot == false && timerj >= 45 && gravity == false && push == false)
				{
					LAnim.Reset();
					currentAnimation = &LAnim;
				}
			}

			if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT
				&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
			{
				position.x += speedx;
				vista = false;
				if (currentAnimation != &RAnim && shot == false && timerj >= 45 && gravity == false && push == false)
				{
					RAnim.Reset();
					currentAnimation = &RAnim;
				}
			}

			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && kick == false)
			{
				shot = true;
				timers = 0;
				if (vista == true)
				{
					App->particles->AddParticle(2, App->particles->lasery, position.x - 3, position.y + 8, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(laserFx);
				}
				else
				{
					App->particles->AddParticle(1, App->particles->laserx, position.x + 15, position.y + 8, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(laserFx);
				}
			}
			timers += 1;
			if (shot == true)
			{
				if (vista == true)
				{
					if (currentAnimation != &shotLAnim)
					{
						shotLAnim.Reset();
						currentAnimation = &shotLAnim;
					}
				}
				else
				{
					if (currentAnimation != &shotRAnim)
					{
						shotRAnim.Reset();
						currentAnimation = &shotRAnim;
					}
				}
				if (timers >= 5)
				{
					shot = false;
				}
			}
		}

		if (timerj >= 45 && gravity == false) {
			if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN)
			{
				timerj = 0;
				high = position.y;
				jump = true;

				//  Asignar W al sonido del jump
				App->audio->PlayFx(jumpFx);
			}
		}
		timerj += 1;
		if (jump == true)
		{
			if (position.y > high - 40)
			{
				position.y -= speedy;
				if (vista == true && currentAnimation != &upRAnim && shot == false) {
					if (currentAnimation != &upLAnim)
					{
						upLAnim.Reset();
						currentAnimation = &upLAnim;
					}
				}
				else if (currentAnimation != &upLAnim && shot == false) {
					if (currentAnimation != &upRAnim)
					{
						upRAnim.Reset();
						currentAnimation = &upRAnim;
					}
				}

				if (position.y <= high - 40)
				{
					jump = false;
					gravity = true;
					high = 0;
				}
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN) {
		if (godmode == false) {
			godmode = true;
			death = true;
		}
		else if (godmode == true) {
			godmode = false;
			death = false;
		}
	}

	if (godmode == true) {
		currentAnimation = &idleRAnim;
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			position.x -= speedx;
			vista = true;
		}
		if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			position.x += speedx;
			vista = false;
		}
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{
			position.y -= speedy;
		}
		if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			position.y += speedy;
		}
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			if (vista == true)
			{
				App->particles->AddParticle(3, App->particles->lasery, position.x - 3, position.y + 8, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
			}
			else
			{
				App->particles->AddParticle(4, App->particles->laserx, position.x + 15, position.y + 8, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
			}
		}

		colliderf->SetPos(600, 600);
		colliderp->SetPos(600, 600);
	}

	if (boulder == true) {
		if (currentAnimation != &rolling)
		{
			rolling.Reset();
			currentAnimation = &rolling;
		}
	}
	if (push == true && destroyed == false) {
		if (vista == true) {
			if (currentAnimation != &pushingL)
			{
				pushingL.Reset();
				currentAnimation = &pushingL;
			}
		}
		else {
			if (currentAnimation != &pushingR)
			{
				pushingR.Reset();
				currentAnimation = &pushingR;
			}
		}
	}
	if (kick == true && destroyed == false) {
		if (vista == true) {
			if (currentAnimation != &kickingL)
			{
				kickingL.Reset();
				currentAnimation = &kickingL;
			}
		}
		else {
			if (currentAnimation != &kickingR)
			{
				kickingR.Reset();
				currentAnimation = &kickingR;
			}
		}
	}

	// If no  movement detected or default floor, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& vista == false
		&& shot == false
		&& jump == false
		&& gravity == false
		&& destroyed == false
		&& boulder == false
		|| App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT
		&& vista == false
		&& shot == false
		&& jump == false
		&& gravity == false
		&& destroyed == false
		&& boulder == false)
		currentAnimation = &idleRAnim;

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& vista == true
		&& shot == false
		&& jump == false
		&& gravity == false
		&& destroyed == false
		&& boulder == false
		|| App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT
		&& vista == true
		&& shot == false
		&& jump == false
		&& gravity == false
		&& destroyed == false
		&& boulder == false)
		currentAnimation = &idleLAnim;

	if (godmode == false) {
		colliderf->SetPos(position.x + 2, position.y + 24);
		colliderp->SetPos(position.x, position.y);
	}

	currentAnimation->Update();

	if (destroyed)
	{
		colliderp->SetPos(600, 600);
		colliderf->SetPos(600, 600);
		destroyedCountdown--;
		if (destroyedCountdown <= 0) {
			jump = false;
			destroyedCountdown = 120;
			if (lives > 0) {
				position.x = 150;
				position.y = 221;
				destroyed = false;
				death = false;
			}
			else if (lives <= 0) {
				App->change->Changing((Module*)App->sceneLevel_1, (Module*)App->screenGameOver, 60);
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x, position.y, &rect);

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == colliderp && destroyed == false && c2->type == Collider::Type::ENEMY)
	{
		if (currentAnimation != &pdead)
		{
			pdead.Reset();
			currentAnimation = &pdead;
		}

		App->audio->PlayFx(deathFx);

		death = true;
		destroyed = true;
		lives--;
	}

	if (c1 == colliderf && c2->type == Collider::Type::FLOOR && jump == false)
	{
		gravity = false;
	}

	if (c1 == colliderf && c2->type == Collider::Type::AIR)
	{
		if (jump == false) {
			gravity = true;
		}
		speedx = 1;
		boulder = false;
		push = false;
		kick = false;
	}

	if (c1 == colliderf && c2->type == Collider::Type::WALL)
	{
		if (vista == false) {
			speedx = 0;
		}
	}

	if (c1 == colliderf && c2->type == Collider::Type::WALL2)
	{
		if (vista == true) {
			speedx = 0;
		}
	}
}