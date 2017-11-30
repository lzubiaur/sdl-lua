#include "catch.hpp"
#include <iostream>
#include "SDL.h"

TEST_CASE("Simple SDL init test", "[RENDERING]") {
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);

    SDL_Quit()
    REQUIRE(false);
}
