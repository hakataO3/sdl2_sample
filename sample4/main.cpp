#include "app.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    sdl2_sample::App *app = sdl2_sample::App::getInstance();
    if (!app->initialize())
    {
        app->run();
    }
    app->finalize();
  
    return 0;
}