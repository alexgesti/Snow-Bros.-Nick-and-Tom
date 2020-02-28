#include "SDL2/include/SDL.h"
#include "SDL2_image/include/SDL_image.h"
#pragma comment ( lib, "SDL2/lib/x86/SDL2.lib")
#pragma comment ( lib, "SDL2/lib/x86/SDL2main.lib")
#pragma comment ( lib, "SDL2_image/lib/x86/SDL2_image.lib")
//Para poner sprites, mirara en la pagina de citm

int main(int argc, char** argv) 
{
	//FASE INICIALIZACION

	SDL_Init(SDL_INIT_EVERYTHING); //Abrir ventana
	SDL_Window* Window = SDL_CreateWindow(0, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN); //crear la ventana
	SDL_Renderer* renderer = SDL_CreateRenderer(Window, -1, 0); //darle un fondo
	SDL_Rect player; //Inicializar un cubo
	SDL_Rect disparo;
	SDL_Event e; //Inicializar eventos

	bool Jump = false;
	bool Right = false;
	bool Left = false;
	bool CanShot = false;
	bool Disparando = false;
	bool DRight = false;
	bool DLeft = false;
	bool End = false;

	float JumpTime = 0;

	player.x = 300;
	player.y = 200;
	player.w = 30;
	player.h = 30;

	disparo.w = 10;
	disparo.h = 10;

	while (End == false)
	{
		//FASE LOGICA
		while (SDL_PollEvent(&e)) //comprueba si hay eventos pendientes
		{
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					Jump = true;
					break;

				case SDLK_RIGHT:
					Right = true;
					if (Disparando == false) DRight = true;
					break;

				case SDLK_LEFT:
					Left = true;
					if (Disparando == false) DLeft = true;
					break;

				case SDLK_d:
					CanShot = true;
					break;

				case SDLK_ESCAPE:
					End = true;
					break;
				}
			}

			if (e.type == SDL_KEYUP)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_RIGHT:
					Right = false;
					if (Disparando == false) DRight = false;
					break;

				case SDLK_LEFT:
					Left = false;
					if (Disparando == false) DLeft = false;
					break;

				case SDLK_d:
					CanShot = false;
					break;
				}
			}
		}

		//Logica salto

		if (Jump)
		{
			JumpTime += 1;
			player.y -= 6.5f;
		}

		//Logica Movimiento

		if (Left == true)
		{
			player.x -= 5;
		}
		if (Right == true)
		{
			player.x += 5;
		}

		if (player.x >= 600)
		{
			player.x = 0;
		}

		//Logica Disparo

		if (CanShot == true && Disparando == false && DRight == true && DLeft == false
			|| CanShot == true && Disparando == false && DLeft == true && DRight == false) Disparando = true;

		if (DRight == true) disparo.x += 10;
		if (DLeft == true) disparo.x -= 10;

		//Resets

		if (JumpTime >= 10)
		{
			Jump = false;
			player.y *= 1.04f;
			if (player.y >= 200)
			{
				player.y = 200;
				JumpTime = 0;
			}
		}

		if (Disparando == false)
		{
			disparo.y = player.y + 10;
			disparo.x = player.x + 10;
		}

		if (disparo.x >= 600 || disparo.x <= 0)
		{
			Disparando = false;
			DRight = false;
			DLeft = false;
		}

		//FASE RENDER

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //Ultimo color llamado = al renderer
		SDL_RenderClear(renderer); //limpia el lienzo

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Darle color cubo
		SDL_RenderDrawRect(renderer, &player); //Dibuja contorno cubo de pantalla
		SDL_RenderFillRect(renderer, &player); //Dibuja cubo por pantalla

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //Darle color cubo
		SDL_RenderDrawRect(renderer, &disparo); //Dibuja contorno cubo de pantalla
		SDL_RenderFillRect(renderer, &disparo); //Dibuja cubo por pantalla

		SDL_RenderPresent(renderer); //actualizar pantalla (que aparezca por pantalla)

		SDL_Delay(30);
	}

	return 0;
}