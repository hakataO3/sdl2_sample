#include "app_sdl.hpp"
#include "SDL2/SDL.h"

namespace app_sdl
{
	AppSDL::AppSDL()
	{
		this->window = NULL;
		this->renderer = NULL;
	}

	AppSDL::~AppSDL()
	{
		if (SDL_WasInit(SDL_INIT_EVERYTHING))
		{
			this->finalize();
		}
	}

	AppSDL *AppSDL::getInstance()
	{
		static AppSDL appSDL;
		return &appSDL;
	}

	int AppSDL::initialize()
	{
		SDL_Init(SDL_INIT_VIDEO);

		this->window =
			SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, 0);
		if (this->window == NULL)
		{
			return 1;
		}

		this->renderer = SDL_CreateRenderer(this->window, -1, 0);
		if (this->renderer == NULL)
		{
			return 1;
		}

		return 0;
	}

	int AppSDL::finalize()
	{
		if (SDL_WasInit(SDL_INIT_EVERYTHING))
		{
			if (this->renderer)
			{
				SDL_DestroyRenderer(this->renderer);
			}
			if (this->window)
			{
				SDL_DestroyWindow(this->window);
			}
			SDL_Quit();
		}

		return 0;
	}

	SDL_Renderer *AppSDL::getRenderer()
	{
		return this->renderer;
	}
}