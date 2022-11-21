#include "game.hpp"

#include "piece.hpp"

void goo()
{
    SDL_Window* window;
    SDL_Init(SDL_INIT_EVERYTHING);
}

Game::Game()
    : is_running_(false) {}

Game::~Game()
{
    // Todo delete pointers
//    destroyEverything();
}

bool Game::isRunning() const
{
    return is_running_;
}

//void Game::initialize()
//{
//    // todo refactor to functions
//    // --- Init SDL ---

//    // Check if SDL init was successful
//    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
//    {
//        throw std::runtime_error("Failed to initialize SDL");
//    }

//    std::cout << "SDL initialized...\n";

//    // --- Window ---

//    const auto window_flags = 0;
//    window_ = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, window_flags);

//    if (window_ == nullptr)
//    {
//        throw std::runtime_error("Failed to create window");
//    }

//    std::cout << "Window created...\n";

//    // --- Renderer ---

//    const auto renderer_flags = 0;
//    const auto renderer_index = -1;
//    renderer_ = SDL_CreateRenderer(window_, renderer_index, renderer_flags);

//    if (renderer_ == nullptr)
//    {
//        throw std::runtime_error("Failed to create renderer");
//    }

//    std::cout << "Renderer created...\n";

//    // --- Initialize other variables ---
//    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255); // Black
//    is_running_ = true;
//}

//void Game::handleEvents()
//{
//    SDL_Event event;
//    SDL_PollEvent(&event);

//    switch (event.type)
//    {
//    case SDL_QUIT:
//        is_running_ = false;
//        break;
//    case SDL_MOUSEBUTTONDOWN:
//        is_running_ = false;
//        break;
//    default:
//        break;
//    }
//}

void Game::update()
{
    // TODO
//    SDL_Init(SDL_INIT_EVERYTHING);
}

//void Game::render()
//{
//    SDL_RenderClear(renderer_);

//    // TODO

//    SDL_RenderPresent(renderer_);
//}

//void Game::destroyEverything()
//{
//    SDL_DestroyWindow(window_);
//    SDL_DestroyRenderer(renderer_);
//}

const auto& Game::getBoard() const
{
    return board_;
}

auto& Game::getBoard()
{
    return board_;
}

const Piece& Game::GetPiece(const Position& position) const
{
    if (board_[position.x][position.y] == nullptr)
    {
        throw std::runtime_error("invalid position");
    }

    return *board_[position.x][position.y].get();
}

Piece& Game::GetPiece(const Position& position)
{
    if (board_[position.x][position.y] == nullptr)
    {
        throw std::runtime_error("invalid position");
    }

    return *board_[position.x][position.y].get();
}

const Position& Game::GetCurrentPosition() const
{
    return current_position_;
}

Position& Game::GetCurrentPosition()
{
    return current_position_;
}
