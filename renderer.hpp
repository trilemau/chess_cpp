#pragma once

#include "libs.hpp"

class Renderer
{
    SDL_Renderer* renderer_;

public:
    Renderer(SDL_Window* window);
    ~Renderer();

    SDL_Renderer* GetRenderer();
};
