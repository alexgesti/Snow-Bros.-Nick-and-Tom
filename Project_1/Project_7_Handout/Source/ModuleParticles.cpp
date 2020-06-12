#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Application.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Nick&Tom.png");
	fire = App->textures->Load("Assets/FIRE.png");

	laserx.anim.PushBack({ 16, 141, 7, 11 });
	laserx.anim.PushBack({ 31, 141, 7, 11 });
	laserx.speedx = 4;
	laserx.speedy = 2;
	laserx.lifetime = 180;
	laserx.anim.speed = 0.2f;

	lasery.anim.PushBack({ 588, 191, 7, 11 });
	lasery.anim.PushBack({ 573, 191, 7, 11 });
	lasery.speedx = 4;
	lasery.speedy = 2;
	lasery.lifetime = 180;
	lasery.anim.speed = 0.2f;

	fireL.anim.PushBack({ 47, 105, 10, 7 });
	fireL.anim.PushBack({ 43, 79, 29, 21 });
	fireL.anim.PushBack({ 38, 54, 19, 12 });
	fireL.anim.PushBack({ 34, 28, 22, 15 });
	fireL.anim.PushBack({ 33, 5, 22, 14 });
	fireL.anim.PushBack({ 12, 100, 16, 20 });
	fireL.anim.PushBack({ 12, 75, 12, 21 });
	fireL.anim.PushBack({ 14, 51, 11, 20 });
	fireL.anim.PushBack({ 14, 27, 10, 18 });
	fireL.speedx = 2;
	fireL.speedy = 0;
	fireL.lifetime = 40;
	fireL.anim.speed = 0.2f;

	fireR.anim.PushBack({ 72, 105, 12, 7 });
	fireR.anim.PushBack({ 72, 79, 31, 21 });
	fireR.anim.PushBack({ 72, 54, 21, 12 });
	fireR.anim.PushBack({ 72, 28, 23, 15 });
	fireR.anim.PushBack({ 72, 5, 22, 14 });
	fireR.anim.PushBack({ 99, 100, 16, 20 });
	fireR.anim.PushBack({ 99, 75, 12, 21 });
	fireR.anim.PushBack({ 99, 51, 11, 20 });
	fireR.anim.PushBack({ 99, 27, 10, 18 });
	fireR.speedx = 2;
	fireR.speedy = 0;
	fireR.lifetime = 40;
	fireR.anim.speed = 0.2f;

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	//App->textures->Unload(texture);

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			if (particle->activate > 0 && particle->activate <= 4) {
				App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			}
			if (particle->activate >= 5 && particle->activate <= 6) {
				App->render->Blit(fire, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(int activate, const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;
			p->activate = activate;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}