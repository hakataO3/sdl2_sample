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
		int texture_height;
		int texture_width;
		int width_pos;
		int height_pos;

		App();
		App(const App&) = delete;
		App& operator=(const App&) = delete;
		App(App&&) = delete;
		App& operator=(App&&) = delete;

		int loadImage();
		int drawMap();
		int draw();
		int update(SDL_Event *event);
		int messageLoop();

	public:
		static App *getInstance();
		~App() = default;
		int initialize();
		int finalize();
		int run();
	};
}