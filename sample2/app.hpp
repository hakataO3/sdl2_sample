#pragma once

#include "SDL2/SDL.h"
#include "app_sdl.hpp"
#include "app_sdl_ttf.hpp"

namespace sdl2_sample
{
	class App final
	{
	private:
		app_sdl::AppSDLttf *font;
		int posY;

		App() = default;
		App(const App&) = delete;
		App& operator=(const App&) = delete;
		App(App&&) = delete;
		App& operator=(App&&) = delete;

		int initialize();
		int finalize();
		int resetLocation();
		char *tos(const int n, char *buff);
		int put(const char *text);
		int putRendererInfo();
		int draw(SDL_Event *event);
		int messageLoop();

	public:
		~App() = default;
		static App *getInstance();
		int run();
	};
}