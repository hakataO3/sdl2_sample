#include "app_sdl_ttf.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

namespace app_sdl
{
	AppSDLttf::AppSDLttf(const char *fontName, const int fontSize)
	{
		this->openFont(fontName, fontSize);
		this->color = {0, 0, 0};
	}

	AppSDLttf::~AppSDLttf()
	{
		this->closeFont();
	}

	int AppSDLttf::openFont(const char *fontName, const int fontSize)
	{
		this->font = TTF_OpenFont(fontName, fontSize);
		
		return 0;
	}

	int AppSDLttf::closeFont()
	{
		TTF_CloseFont(this->font);

		return 0;
	}

	int AppSDLttf::setStyle(const int style)
	{
		TTF_SetFontStyle(this->font, style);

		return 0;
	}

	int AppSDLttf::setColor(const SDL_Color color)
	{
		this->color = color;

		return 0;
	}

	SDL_Surface *AppSDLttf::render(const char *text)
	{
		if (this->font != NULL)
		{
			return TTF_RenderUTF8_Blended(this->font, text, this->color);
		}
		
		return NULL;
	}
}