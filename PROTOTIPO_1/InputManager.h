/*#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H
#include "SDL2/include/SDL.h"

class InputManager
{
	static InputManager* sInstance;

	const Uint8* mKeyboardStates;

	public:
		static InputManager* Instance();
		static void Release();

		bool KeyDown(SDL_Scancode scanCode);
		
		void Update();

		InputManager();
		~InputManager();
};

#endif */

