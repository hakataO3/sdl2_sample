#include "app.hpp"
#include <string>
#include <cstdlib>
#include "SDL2/SDL.h"
#include "app_sdl.hpp"
#include "app_sdl_ttf.hpp"

namespace sdl2_sample
{
	App *App::getInstance()
	{
		static App app;
		return &app;
	}

	int App::initialize()
	{		
		app_sdl::AppSDL::getInstance()->initialize();
		
		this->font = new app_sdl::AppSDLttf("/system/fonts/DroidSans.ttf", 36);
		
		return 0;
	}
	
	int App::finalize()
	{
		if (this->font != NULL)
		{
			delete this->font;
		}
		
		app_sdl::AppSDL::getInstance()->finalize();
		
		return 0;
	}
	
	int App::resetLocation()
	{
		this->posY = 0;
		
		return 0;
	}
	
	char *App::tos(const int n, char *buff)
	{
		sprintf(buff, "%d", n);
		return buff;
	}

	int App::put(const char *text)
	{
		SDL_Renderer *renderer = app_sdl::AppSDL::getInstance()->getRenderer();
		
		SDL_Surface *surface = this->font->render(text);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
		
		SDL_Rect rect = {0, this->posY, surface->w, surface->h};
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		this->posY += surface->h;
		
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);

		return 0;
	}
	
	int App::putRendererInfo()
	{
		SDL_Renderer *renderer = app_sdl::AppSDL::getInstance()->getRenderer();
		
		SDL_Color color = {255, 255, 0};
		this->font->setColor(color);

		SDL_RendererInfo info;
		SDL_GetRendererInfo(renderer, &info);
		
		this->put("Renderer information");
		
		std::string str = "name=";
		str += info.name;
		this->put(str.c_str());
		
		char buff[64];
		str = "flags=";
		//str += std::to_string(info.flags);
		str += this->tos(info.flags, buff);
		this->put(str.c_str());
		
		str = "num_texture_formats=";
		//str += std::to_string(info.num_texture_formats);
		str += this->tos(info.num_texture_formats, buff);
		this->put(str.c_str());
		
		//str = "texture_formats=";
		//str += std::to_string(info.texture_formats);
		//str += this->tos(info.texture_formats, buff);
		//this->put(str.c_str());
		
		str = "max_texture_width=";
		//str += std::to_string(max_tecture_width);
		str += this->tos(info.max_texture_width, buff);
		this->put(str.c_str());
		
		str = "max_texture_height=";
		//str += std::to_string(max_tecture_height);
		str += this->tos(info.max_texture_height, buff);
		this->put(str.c_str());
		
		this->put(" ");

		return 0;
	}

	int App::draw(SDL_Event *event)
	{
		SDL_Renderer *renderer = app_sdl::AppSDL::getInstance()->getRenderer();
		
		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		SDL_RenderClear(renderer);
		
		this->resetLocation();
		this->putRendererInfo();
		
		SDL_RenderPresent(renderer);
		
		return 0;
	}

	int App::messageLoop()
	{
		SDL_Event event;
		
		while (true)
		{
			if (SDL_PollEvent(&event))
			{
				if (event.type == SDL_FINGERUP)
				{
					break;
				}
				
				this->draw(&event);
			}
		}

		return 0;
	}
	
	int App::run()
	{
		this->initialize();
		this->messageLoop();
		this->finalize();
		
		return 0;
	}
}