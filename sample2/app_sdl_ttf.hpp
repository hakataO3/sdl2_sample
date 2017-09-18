#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

namespace app_sdl
{
	class AppSDLttf
	{
	private:
		TTF_Font *font;
		SDL_Color color;

		int openFont(const char *fontName, const int fontSize);
		int closeFont();

	 public:
		AppSDLttf() = delete;
		AppSDLttf(const char *fontName, const int fontSize);
		~AppSDLttf();
		int setStyle(const int style);
		int setColor(const SDL_Color color);
		SDL_Surface *render(const char* text);
	};
}