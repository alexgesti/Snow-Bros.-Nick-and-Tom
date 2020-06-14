#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::WALL2] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::WALL][Collider::Type::AIR] = false;
	matrix[Collider::Type::WALL][Collider::Type::FEET] = true;
	matrix[Collider::Type::WALL][Collider::Type::FISICSNOW] = true;
	matrix[Collider::Type::WALL][Collider::Type::DELSNOW] = false;
	matrix[Collider::Type::WALL][Collider::Type::SNOWBALL] = true;
	matrix[Collider::Type::WALL][Collider::Type::FEETEN] = false;

	matrix[Collider::Type::WALL2][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL2][Collider::Type::WALL2] = false;
	matrix[Collider::Type::WALL2][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL2][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL2][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL2][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::WALL2][Collider::Type::AIR] = false;
	matrix[Collider::Type::WALL2][Collider::Type::FEET] = true;
	matrix[Collider::Type::WALL2][Collider::Type::FISICSNOW] = true;
	matrix[Collider::Type::WALL2][Collider::Type::DELSNOW] = false;
	matrix[Collider::Type::WALL2][Collider::Type::SNOWBALL] = true;
	matrix[Collider::Type::WALL2][Collider::Type::FEETEN] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WALL2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::FLOOR] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::AIR] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::FEET] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::FISICSNOW] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::DELSNOW] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::SNOWBALL] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::FEETEN] = false;

	matrix[Collider::Type::FEET][Collider::Type::WALL] = true;
	matrix[Collider::Type::FEET][Collider::Type::WALL2] = true;
	matrix[Collider::Type::FEET][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::FEET][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::FEET][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::FEET][Collider::Type::FLOOR] = true;
	matrix[Collider::Type::FEET][Collider::Type::AIR] = true;
	matrix[Collider::Type::FEET][Collider::Type::FEET] = false;
	matrix[Collider::Type::FEET][Collider::Type::FISICSNOW] = true;
	matrix[Collider::Type::FEET][Collider::Type::DELSNOW] = false;
	matrix[Collider::Type::FEET][Collider::Type::SNOWBALL] = true;
	matrix[Collider::Type::FEET][Collider::Type::FEETEN] = false;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::WALL2] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::AIR] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::FEET] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::FISICSNOW] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::DELSNOW] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::SNOWBALL] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::FEETEN] = false;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL2] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::FLOOR] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::AIR] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::FEET] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::FISICSNOW] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::DELSNOW] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::SNOWBALL] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::FEETEN] = false;

	matrix[Collider::Type::FLOOR][Collider::Type::WALL] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::WALL2] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::FLOOR][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::FLOOR][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::FLOOR][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::AIR] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::FEET] = true;
	matrix[Collider::Type::FLOOR][Collider::Type::FISICSNOW] = true;
	matrix[Collider::Type::FLOOR][Collider::Type::DELSNOW] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::SNOWBALL] = true;
	matrix[Collider::Type::FLOOR][Collider::Type::FEETEN] = false;

	matrix[Collider::Type::AIR][Collider::Type::WALL] = false;
	matrix[Collider::Type::AIR][Collider::Type::WALL2] = false;
	matrix[Collider::Type::AIR][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::AIR][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::AIR][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::AIR][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::AIR][Collider::Type::AIR] = false;
	matrix[Collider::Type::AIR][Collider::Type::FEET] = true;
	matrix[Collider::Type::AIR][Collider::Type::FISICSNOW] = true;
	matrix[Collider::Type::AIR][Collider::Type::DELSNOW] = false;
	matrix[Collider::Type::AIR][Collider::Type::SNOWBALL] = true;
	matrix[Collider::Type::AIR][Collider::Type::FEETEN] = false;

	matrix[Collider::Type::FISICSNOW][Collider::Type::WALL] = true;
	matrix[Collider::Type::FISICSNOW][Collider::Type::WALL2] = true;
	matrix[Collider::Type::FISICSNOW][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::FISICSNOW][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::FISICSNOW][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::FISICSNOW][Collider::Type::FLOOR] = true;
	matrix[Collider::Type::FISICSNOW][Collider::Type::AIR] = true;
	matrix[Collider::Type::FISICSNOW][Collider::Type::FEET] = true;
	matrix[Collider::Type::FISICSNOW][Collider::Type::FISICSNOW] = true;
	matrix[Collider::Type::FISICSNOW][Collider::Type::DELSNOW] = true;
	matrix[Collider::Type::FISICSNOW][Collider::Type::SNOWBALL] = true;
	matrix[Collider::Type::FISICSNOW][Collider::Type::FEETEN] = false;

	matrix[Collider::Type::DELSNOW][Collider::Type::WALL] = false;
	matrix[Collider::Type::DELSNOW][Collider::Type::WALL2] = false;
	matrix[Collider::Type::DELSNOW][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::DELSNOW][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::DELSNOW][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::DELSNOW][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::DELSNOW][Collider::Type::AIR] = false;
	matrix[Collider::Type::DELSNOW][Collider::Type::FEET] = false;
	matrix[Collider::Type::DELSNOW][Collider::Type::FISICSNOW] = true;
	matrix[Collider::Type::DELSNOW][Collider::Type::DELSNOW] = false;
	matrix[Collider::Type::DELSNOW][Collider::Type::SNOWBALL] = true;
	matrix[Collider::Type::DELSNOW][Collider::Type::FEETEN] = false;

	matrix[Collider::Type::SNOWBALL][Collider::Type::WALL] = true;
	matrix[Collider::Type::SNOWBALL][Collider::Type::WALL2] = true;
	matrix[Collider::Type::SNOWBALL][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::SNOWBALL][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::SNOWBALL][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::SNOWBALL][Collider::Type::FLOOR] = true;
	matrix[Collider::Type::SNOWBALL][Collider::Type::AIR] = true;
	matrix[Collider::Type::SNOWBALL][Collider::Type::FEET] = true;
	matrix[Collider::Type::SNOWBALL][Collider::Type::FISICSNOW] = true;
	matrix[Collider::Type::SNOWBALL][Collider::Type::DELSNOW] = true;
	matrix[Collider::Type::SNOWBALL][Collider::Type::SNOWBALL] = true;
	matrix[Collider::Type::SNOWBALL][Collider::Type::FEETEN] = false;

	matrix[Collider::Type::FEETEN][Collider::Type::WALL] = false;
	matrix[Collider::Type::FEETEN][Collider::Type::WALL2] = false;
	matrix[Collider::Type::FEETEN][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::FEETEN][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::FEETEN][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::FEETEN][Collider::Type::FLOOR] = true;
	matrix[Collider::Type::FEETEN][Collider::Type::AIR] = true;
	matrix[Collider::Type::FEETEN][Collider::Type::FEET] = false;
	matrix[Collider::Type::FEETEN][Collider::Type::FISICSNOW] = false;
	matrix[Collider::Type::FEETEN][Collider::Type::DELSNOW] = false;
	matrix[Collider::Type::FEETEN][Collider::Type::SNOWBALL] = false;
	matrix[Collider::Type::FEETEN][Collider::Type::FEETEN] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

update_status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->Intersects(c2->rect))
			{
				if (matrix[c1->type][c2->type] && c1->listener)
					c1->listener->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->listener)
					c2->listener->OnCollision(c2, c1);
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return update_status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::AIR: // purplef
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha - 70);
			break;
		case Collider::Type::WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::WALL2: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::FEET: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::ENEMY: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case Collider::Type::PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case Collider::Type::FLOOR: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::FISICSNOW: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case Collider::Type::SNOWBALL: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case Collider::Type::DELSNOW: // cyan
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}
