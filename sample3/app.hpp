#pragma once

#include "SDL2/SDL.h"

namespace sdl2_sample
{
	class App final
	{
	private:
		SDL_Window *sdl_window;
		SDL_Renderer *sdl_renderer;
		SDL_Surface *sdl_surface;
		SDL_Texture *sdl_texture;

		App();
		App(const App&) = delete;
		App& operator=(const App&) = delete;
		App(App&&) = delete;
		App& operator=(App&&) = delete;

		int loadImage();
		int draw();
		int messageLoop();

	public:
		static App *getInstance();
		~App() = default;
		int initialize();
		int finalize();
		int run();
	};
}