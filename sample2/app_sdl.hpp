#pragma once

#include "SDL2/SDL.h"

namespace app_sdl
{
	class AppSDL final
	{
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;

		AppSDL();
		AppSDL(const AppSDL&) = delete;
		AppSDL& operator=(const AppSDL&) = delete;
		AppSDL(AppSDL&&) = delete;
		AppSDL& operator=(AppSDL&&) = delete;

	public:
		~AppSDL();
		static AppSDL *getInstance();
		int initialize();
		int finalize();
		SDL_Renderer *getRenderer();
	};
}