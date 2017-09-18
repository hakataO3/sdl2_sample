#include "app.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

namespace sdl2_sample
{
	App *App::getInstance()
	{
		static App app;
		return &app;
	}

	App::App()
	{
		this->sdl_window = NULL;
		this->sdl_renderer = NULL;
		this->sdl_surface = NULL;
		this->sdl_texture = NULL;
	}

	int App::initialize()
	{
		if (!SDL_WasInit(SDL_INIT_EVERYTHING))
		{
			if (SDL_Init(SDL_INIT_VIDEO))
			{
				return 1;
			}

			this->sdl_window =
				SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, 0);
			if (this->sdl_window == NULL)
			{
				return 1;
			}

			this->sdl_renderer = SDL_CreateRenderer(this->sdl_window, -1, 0);
			if (this->sdl_renderer == NULL)
			{
				return 1;
			}

			int initImage = IMG_INIT_PNG;
			if ((IMG_Init(initImage) & initImage) != initImage)
			{
				return 1;
			}
		}

		return 0;
	}

	int App::finalize()
	{
		if (SDL_WasInit(SDL_INIT_EVERYTHING))
		{
			if (this->sdl_surface)
			{
				SDL_FreeSurface(this->sdl_surface);
			}
			IMG_Quit();

			if (this->sdl_texture)
			{
				SDL_DestroyTexture(this->sdl_texture);
			}
			if (this->sdl_renderer)
			{
				SDL_DestroyRenderer(this->sdl_renderer);
			}
			if (this->sdl_window)
			{
				SDL_DestroyWindow(this->sdl_window);
			}
			SDL_Quit();
		}

		return 0;
	}

	int App::loadImage()
	{
		this->sdl_surface = IMG_Load("background256.png");
		if (this->sdl_surface == NULL)
		{
			return 1;
		}

		this->sdl_texture = SDL_CreateTextureFromSurface(this->sdl_renderer, this->sdl_surface);
		if (this->sdl_texture == NULL)
		{
			return 1;
		}

		return 0;
	}

	int App::draw()
	{
		SDL_SetRenderDrawColor(this->sdl_renderer, 0, 0, 0, 255);
		SDL_RenderClear(this->sdl_renderer);

		SDL_RenderCopy(this->sdl_renderer, this->sdl_texture, NULL, NULL);

		SDL_RenderPresent(this->sdl_renderer);

		return 0;
	}

	int App::messageLoop()
	{
		SDL_Event event;

		while (true)
		{
			SDL_PollEvent(&event);
			if (event.type == SDL_FINGERUP)
			{
				break;
			}

			this->draw();
		}

		return 0;
	}

	int App::run()
	{
		if (!this->loadImage())
		{
			if (this->messageLoop())
			{
				return 1;
			}
		}

		return 0;
	}
}