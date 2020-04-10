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
	idleAnim.PushBack({ 16, 16, 21, 27 });

	// move upwards
	upRAnim.PushBack({ 16, 305, 20, 29 });
	upRAnim.PushBack({ 44, 307, 22, 27 });
	upRAnim.PushBack({ 74, 311, 20, 23 });
	upRAnim.PushBack({ 102, 312, 20, 22 });
	upRAnim.PushBack({ 130, 307 , 20, 27 });
	upRAnim.PushBack({ 159, 311, 20, 24 });
	upRAnim.PushBack({ 186, 311, 23, 23 });
	upRAnim.PushBack({ 217, 305, 20, 29 });
	upRAnim.loop = false;
	upRAnim.speed = 0.15f;

	upLAnim.PushBack({ 546, 132, 20, 29 });
	upLAnim.PushBack({ 516, 134, 22, 27 });
	upLAnim.PushBack({ 488, 138, 20, 23 });
	upLAnim.PushBack({ 460, 139, 20, 22 });
	upLAnim.PushBack({ 432, 134, 20, 27 });
	upLAnim.PushBack({ 404, 137, 20, 24 });
	upLAnim.PushBack({ 137, 138, 23, 23 });
	upLAnim.PushBack({ 345, 132, 20, 29 });
	upLAnim.loop = false;
	upLAnim.speed = 0.15f;

	RAnim.PushBack({ 16, 76, 18, 28});
	RAnim.PushBack({ 42, 77, 16, 27 });
	RAnim.PushBack({ 66, 76, 19, 28 });
	RAnim.PushBack({ 93, 77, 16, 27 });
	RAnim.loop = true;
	RAnim.speed = 0.1f;

	LAnim.PushBack({ 548, 79, 18, 28 });
	LAnim.PushBack({ 524, 80, 16, 27 });
	LAnim.PushBack({ 497, 79, 19, 28 });
	LAnim.PushBack({ 473, 80, 16, 27 });
	LAnim.loop = true;
	LAnim.speed = 0.1f;

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Nick&Tom.png");
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/shot.wav"); // laser.wav por shot.wav
	// añadí sonidos del salto y muerte
	jumpFx = App->audio->LoadFx("Assets/jump.wav");
	deathFx = App->audio->LoadFx("Assets/death.wav");


	position.x = 150;
	position.y = 120;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	position.x += speed;
	if (death == false) {
		//Gravedad
		if (position.y < 120 && jump == false)
		{
			position.y += speed * 1.5;
		}

		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			position.x -= speed;
			if (currentAnimation != &LAnim && jump == false)
			{
				LAnim.Reset();
				currentAnimation = &LAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			position.x += speed;
			if (currentAnimation != &RAnim && jump == false)
			{
				RAnim.Reset();
				currentAnimation = &RAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN)
		{
			high = position.y;
			large = position.x;
			jump = true;

			//  para asignar W al sonido del jump
			App->audio->PlayFx(jumpFx);
		}
		if (jump == true && position.y > high - 30)
		{
			position.y -= speed;
			if (position.x <= large) {
				if (currentAnimation != &upLAnim)
				{
					upRAnim.Reset();
					currentAnimation = &upLAnim;
				}
			}
			else {
				if (currentAnimation != &upRAnim)
				{
					upRAnim.Reset();
					currentAnimation = &upRAnim;
				}
			}

			if (position.y <= high - 30)
			{
				jump = false;
			}
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
				App->particles->AddParticle(App->particles->lasery, position.x - 9, position.y + 8, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
			}
			else {
				App->particles->AddParticle(App->particles->laserx, position.x + 20, position.y + 8, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
			}
		}
	}  

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_DOWN) {
		return update_status::UPDATE_STOP;
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE 
		&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
		currentAnimation = &idleAnim;
	

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
}