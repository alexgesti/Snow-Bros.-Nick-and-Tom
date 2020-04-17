#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer()
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

	shotLAnim.PushBack({ 420, 81, 21, 26 });
	shotLAnim.PushBack({ 392, 78, 20, 29 });
	shotLAnim.PushBack({ 357, 80, 27, 27 });
	shotLAnim.PushBack({ 322, 80, 27, 27 });
	shotLAnim.loop = false;
	shotLAnim.speed = 0.25f;

	shotRAnim.PushBack({ 141, 78, 21, 26 });
	shotRAnim.PushBack({ 170, 75, 20, 29 });
	shotRAnim.PushBack({ 198, 77, 27, 27 });
	shotRAnim.PushBack({ 233, 77, 27, 27});
	shotRAnim.loop = false;
	shotRAnim.speed = 0.25f;
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

	laserFx = App->audio->LoadFx("Assets/shot.wav"); // laser.wav por shot.wav
	// añadí sonidos del salto y muerte
	jumpFx = App->audio->LoadFx("Assets/jump.wav");
	deathFx = App->audio->LoadFx("Assets/death.wav");

	position.x = 150;
	position.y = 220;

	collider = App->collisions->AddCollider({ position.x, position.y, 21, 27 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	if (death == false) {
		//Gravedad
		if (position.y < 220 && jump == false)//cambiarlo por colisiones
		{
			position.y += speed * 1.5;
			if (vista ==  1) {
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

		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT 
			&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
		{
			position.x -= speed;
			vista = true;
			if (currentAnimation != &LAnim && shot == false && timerj >= 75)//coli-
			{
				LAnim.Reset();
				currentAnimation = &LAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT 
			&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
		{
			position.x += speed;
			vista = false;
			if (currentAnimation != &RAnim && shot == false && timerj >= 75)// -siones
			{
				RAnim.Reset();
				currentAnimation = &RAnim;
			}
		}

		if (timerj >= 75) { //bye bye timer, hola colisiones
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
		if (jump == true && shot == false)
		{
			if (position.y > high - 40)
			{
				position.y -= speed;
				if (vista == true && currentAnimation != &upRAnim) {
					if (currentAnimation != &upLAnim)
					{
						upLAnim.Reset();
						currentAnimation = &upLAnim;
					}
				}
				else if (currentAnimation != &upLAnim) {
					if (currentAnimation != &upRAnim)
					{
						upRAnim.Reset();
						currentAnimation = &upRAnim;
					}
				}

				if (position.y <= high - 40)
				{
					jump = false;
					high = 0;
				}
			}
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			shot = true;
			timers = 0;
			if (vista == true) 
			{
				App->particles->AddParticle(App->particles->lasery, position.x - 3, position.y + 8, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
			}
			else 
			{
				App->particles->AddParticle(App->particles->laserx, position.x + 15, position.y + 8, Collider::Type::PLAYER_SHOT);
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
			if (timers >= 10) 
			{
				shot = false;
			}
		}
	}  

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_DOWN) {
		return update_status::UPDATE_STOP;
	}
	

	// If no  movement detected or default floor, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& position.y >= 220  //mas colisiones
		&& vista == false 
		&& shot == false
		|| App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT
		&& position.y >= 220  //mas colisiones
		&& vista == false
		&& shot == false)
		currentAnimation = &idleRAnim;

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& position.y >= 220  //mas colisiones
		&& vista == true
		&& shot == false
		|| App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT
		&& position.y >= 220  //mas colisiones
		&& vista == true
		&& shot == false)
		currentAnimation = &idleLAnim;
	

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	if (destroyed)
	{
		death = true;
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	 if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);

		App->audio->PlayFx(deathFx);

		destroyed = true;
	}
	
	 
	/*if ()
	{
		LOG("Destroyed");
	}*/

}