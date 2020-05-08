#include "Particle.h"

#include "Collider.h"

Particle::Particle()
{
	position.SetToZero();
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speedx(p.speedx), speedy(p.speedy),
										frameCount(p.frameCount), lifetime(p.lifetime)
{

}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool Particle::Update()
{
	bool ret = true;
	frameCount++;

	// The particle is set to 'alive' when the delay has been reached
	if (!isAlive && frameCount >= 0)
		isAlive = true;

	if (isAlive)
	{
		anim.Update();

		// If the particle has a specific lifetime, check when it has to be destroyed
		if (lifetime > 0)
		{
			if (frameCount >= lifetime)
				ret = false;
		}
		// Otherwise the particle is destroyed when the animation is finished
		else if (anim.HasFinished())
			ret = false;

		// Update the position in the screen
		if (activate == 1) {
			position.x += speedx;
			countdown += 1;
			if (countdown >= 10) {
				position.y += speedy;
				if (speedx > 0) {
					speedx -= 0.5f;
				}
			}
		}
		if (activate == 2) {
			position.x -= speedx;
			countdown += 1;
			if (countdown >= 10) {
				position.y += speedy;
				if (speedx > 0) {
					speedx -= 0.5f;
				}
			}
		}
		if (activate == 0){
			position.x += speedx;
			position.y += speedy;
		}

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}

	return ret;
}