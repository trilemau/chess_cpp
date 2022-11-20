#pragma once

#include "libs.hpp"

class Texture
{
    SDL_Texture* texture_;

public:
    Texture(SDL_Renderer* renderer, const string& texture_file);
    ~Texture();

    SDL_Texture* GetTexture();
};
