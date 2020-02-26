#include "SDL2/include/SDL.h"
#pragma comment ( lib, "SDL2/lib/x86/SDL2.lib")
#pragma comment ( lib, "SDL2/lib/x86/SDL2main.lib")

int main(int argc, char** argv) 
{
	//FASE INICIALIZACION

	SDL_Init(SDL_INIT_EVERYTHING); //Abrir ventana
	SDL_Window* Window = SDL_CreateWindow(0, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN); //crear la ventana
	SDL_Renderer* renderer = SDL_CreateRenderer(Window, -1, 0); //darle un fondo
	SDL_Rect player; //Inicializar un cubo
	SDL_Event e; //Inicializar eventos


	player.x = 300;
	player.y = 200;
	player.w = 30;
	player.h = 30;

	while (1)
	{
		//FASE LOGICA
		while (SDL_PollEvent(&e)) //comprueba si hay eventos pendientes
		{
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					player.y -= 5;
					break;

				case SDLK_DOWN:
					player.y += 5;
					break;

				case SDLK_RIGHT:
					player.x += 5;
					break;

				case SDLK_LEFT:
					player.x -= 5;
					break;

				default:
					break;
				}
			}
		}

		if (player.x >= 600)
		{
			player.x = 0;
		}

		//FASE RENDER

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //Ultimo color llamado = al renderer
		SDL_RenderClear(renderer); //limpia el lienzo

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Darle color cubo
		SDL_RenderDrawRect(renderer, &player); //Dibuja contorno cubo de pantalla
		SDL_RenderFillRect(renderer, &player); //Dibuja cubo por pantalla

		SDL_RenderPresent(renderer); //actualizar pantalla (que aparezca por pantalla)

		SDL_Delay(30);
	}

	return 0;
}