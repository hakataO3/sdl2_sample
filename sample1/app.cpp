#include "app.hpp"
#include "SDL2/SDL.h"
#include "app_sdl.hpp"

namespace sdl2_sample
{
	App *App::getInstance()
	{
		static App app;
		return &app;
	}

	int App::draw()
	{
		SDL_Renderer *renderer = app_sdl::AppSDL::getInstance()->getRenderer();

		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, 10, 10, 400, 400);
	
		SDL_Rect rect = (SDL_Rect){100,100,100,100};
		SDL_RenderFillRect(renderer, &rect);
	
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &rect);
	
		SDL_RenderPresent(renderer);

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
		app_sdl::AppSDL *sdl = app_sdl::AppSDL::getInstance();
		sdl->initialize();
		this->messageLoop();
		sdl->finalize();
		
		return 0;
	}
}