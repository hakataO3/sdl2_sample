#include "app_sdl.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

namespace app_sdl
{
	AppSDL::AppSDL()
	{
		this->window = NULL;
		this->renderer = NULL;
	}

	AppSDL::~AppSDL()
	{
		this->finalize();
	}

	AppSDL *AppSDL::getInstance()
	{
		static AppSDL appSDL;
		return &appSDL;
	}

	int AppSDL::initialize()
	{
		int ret = SDL_Init(SDL_INIT_VIDEO);
		if (ret != 0)
		{
			return 1;
		}

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

		ret = TTF_Init();
		if (ret != 0)
		{
			return 1;
		}
		
		return 0;
	}

	int AppSDL::finalize()
	{
		if (TTF_WasInit())
		{
			TTF_Quit();
		}

		if (SDL_WasInit(0))
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