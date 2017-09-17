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
		this->texture_height = 0;
		this->texture_width = 0;
		this->width_pos = 0;
		this->height_pos = 0;
	}

	int App::initialize()
	{
		if (!SDL_WasInit(SDL_INIT_EVERYTHING))
		{
			if (SDL_Init(SDL_INIT_VIDEO))
			{
				return 1;
			}

			this->sdl_window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, 0);
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

		SDL_QueryTexture(this->sdl_texture, NULL, NULL, &this->texture_width, &this->texture_height);
        SDL_RenderSetLogicalSize(this->sdl_renderer, this->texture_width, this->texture_height);
        
		return 0;
	}

	int App::drawMap()
	{
		SDL_Rect src;
		SDL_Rect dst;

		src.x = this->width_pos;
		src.y = this->height_pos;
		src.w = this->texture_width - this->width_pos;
		src.h = this->texture_height - this->height_pos;

		dst.x = 0;
		dst.y = 0;
		dst.w = this->texture_width - this->width_pos;
		dst.h = this->texture_height - this->height_pos;

		SDL_RenderCopy(this->sdl_renderer, this->sdl_texture, &src, &dst);

		if (this->height_pos != 0)
		{
			src.x = this->width_pos;
			src.y = 0;
			src.w = this->texture_width - this->width_pos;
			src.h = this->height_pos;

			dst.x = 0;
			dst.y = this->texture_height - this->height_pos;
			dst.w = this->texture_width - this->width_pos;
			dst.h = this->height_pos;

			SDL_RenderCopy(this->sdl_renderer, this->sdl_texture, &src, &dst);
		}

		if (this->width_pos != 0)
		{
			src.x = 0;
			src.y = this->height_pos;
			src.w = this->width_pos;
			src.h = this->texture_height - this->height_pos;

			dst.x = this->texture_width - this->width_pos;
			dst.y = 0;
			dst.w = this->width_pos;
			dst.h = this->texture_height - this->height_pos;

			SDL_RenderCopy(this->sdl_renderer, this->sdl_texture, &src, &dst);

			if (this->height_pos != 0)
			{
				src.x = 0;
				src.y = 0;
				src.w = this->width_pos;
				src.h = this->height_pos;

				dst.x = this->texture_width - this->width_pos;
				dst.y = this->texture_height - this->height_pos;
				dst.w = this->width_pos;
				dst.h = this->height_pos;

				SDL_RenderCopy(this->sdl_renderer, this->sdl_texture, &src, &dst);
			}
		}

		return 0;
	}

	int App::draw()
	{
		SDL_SetRenderDrawColor(this->sdl_renderer, 0, 0, 0, 255);
		SDL_RenderClear(this->sdl_renderer);

		this->drawMap();

		SDL_RenderPresent(this->sdl_renderer);

		return 0;
	}

	int App::update(SDL_Event * event)
	{
		int movex = 0;
		int movey = 0;
		if (event->type == SDL_FINGERMOTION)
		{
		    SDL_TouchFingerEvent *fe = &event->tfinger;

			if ((fe->x + fe->dx) < 0.4)
			{
				movex = 4;
			}
			else if ((fe->x + fe->dx) > 0.6)
			{
				movex = -4;
			}

			if ((fe->y + fe->dy) < 0.4)
			{
				movey = 4;
			}
			else if ((fe->y + fe->dy) > 0.6)
			{
				movey = -4;
			}
		}

		this->width_pos += movex;
		if (this->width_pos > this->texture_width)
		{
			this->width_pos = 0;
		}
		else if (this->width_pos < 0)
		{
			this->width_pos = this->texture_width;
		}

		this->height_pos += movey;
		if (this->height_pos > this->texture_height)
		{
			this->height_pos = 0;
		}
		else if (this->height_pos < 0)
		{
			this->height_pos = this->texture_height;
		}

		return 0;
	}

	int App::messageLoop()
	{
	    Uint32 interval = 1000 / 60;
		SDL_Event event;
		Uint32 now = SDL_GetTicks();
		Uint32 timeout = now + interval;

		while (true)
		{
			SDL_PollEvent(&event);
			if (event.type == SDL_MULTIGESTURE)
			{
				SDL_MultiGestureEvent *ge = &event.mgesture;			
				if (ge->numFingers > 2)
				{
				    break;
				}
			}

			now = SDL_GetTicks();
			if (SDL_TICKS_PASSED(now, timeout))
			{
				this->update(&event);
				this->draw();
				timeout = now + interval;
			}
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