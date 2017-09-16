#pragma once

#include "app_sdl.hpp"

namespace sdl2_sample
{
	class App final
	{
	  private:
		App() = default;
		App(const App&) = delete;
		App& operator=(const App&) = delete;
		App(App&&) = delete;
		App& operator=(App&&) = delete;
		
		int draw();
		int messageLoop();

	  public:
		~App() = default;
		static App *getInstance();
		int run();
	};
}