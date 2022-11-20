#include "renderer.hpp"

Renderer::Renderer(SDL_Window* window)
{
    renderer_= SDL_CreateRenderer(window, -1, 0);

    // Check if renderer was created successfully
    if (renderer_ == nullptr)
    {
        std::cerr << "Renderer error=" << SDL_GetError() << '\n';
        throw std::runtime_error("Failed to create renderer\n");
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer_);
}

SDL_Renderer* Renderer::GetRenderer()
{
    return renderer_;
}
