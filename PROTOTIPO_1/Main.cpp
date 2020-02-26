#include "SDL2/include/SDL.h"
#pragma comment ( lib, "SDL2/lib/x86/SDL2.lib")
#pragma comment ( lib, "SDL2/lib/x86/SDL2main.lib")

int main(int argc, char** argv) 
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* Window = SDL_CreateWindow(0, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);;
	SDL_Renderer* renderer = SDL_CreateRenderer(Window, -1 , 0);
	SDL_Rect player;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	player.x = 300;
	player.y = 200;
	player.w = 30;
	player.h = 30;

	SDL_RenderPresent(renderer);


	system("pause");
	
	return 0;
}