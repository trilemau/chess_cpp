#include "texture.hpp"

Texture::Texture(SDL_Renderer* renderer, const string& texture_file)
{
    IMG_Init(IMG_INIT_PNG);

    texture_ = IMG_LoadTexture(renderer, texture_file.c_str());

    // Check if texture was loaded correctly
    if (texture_ == nullptr)
    {
        std::cerr << "Texture error=" << SDL_GetError() << '\n';
        throw std::runtime_error("Failed to create texture\n");
    }
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture_);
}

SDL_Texture* Texture::GetTexture()
{
 return texture_;
}

// TODO delete not neededd
