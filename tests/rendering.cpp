#include "catch.hpp"
#include <iostream>
#include <SDL.h>

TEST_CASE("Simple SDL window test", "[RENDERING]") {
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_Window *window = SDL_CreateWindow (
        "An SDL2 window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    bool quit = false;
    SDL_Event e;
    while (quit == false) {
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_KEYDOWN){
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
    }

    SDL_DestroyWindow(window);
}
