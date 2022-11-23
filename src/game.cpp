#include "game.hpp"

#include "king.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "pawn.hpp"

bool CanMove(int old_column_index, int old_row_index, int new_column_index, int new_row_index)
{
    // Check if the old and new position is the same
    if (new_column_index == old_column_index && new_row_index == old_row_index)
    {
        return false;
    }

    // TODO
    // Check if the new position is taken by the same color pieces


    // TODO casltling
    return true;
}

Game::Game()
    : is_running_(false)
{

}

Game::~Game()
{
    destroyEverything();
}

bool Game::isRunning() const
{
    return is_running_;
}

bool Game::initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cout << "Failed to initialize SDL=" << SDL_GetError();
        return false;
    }

    std::cout << "SDL initialized...\n";

    SDL_Window* window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::cerr << "Failed to create window=" << SDL_GetError();
        return false;
    }

    std::cout << "Window created...\n";

    renderer_= SDL_CreateRenderer(window, -1, 0); // TODO values to constants

    // Check if renderer was created successfully
    if (renderer_ == nullptr)
    {
        std::cerr << "Failed to create window=" << SDL_GetError();
        return false;
    }

    std::cout << "Renderer created...\n";

    if (Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, SOUND_CHANNELS, SOUND_CHUNKS) == SOUND_ERROR)
    {
        std::cerr << "Failed to initialize audio=" << Mix_GetError();
        return EXIT_FAILURE;
    }

    std::cout << "Audio initialized...\n";

    move_piece_sfx_ = Mix_LoadWAV("sounds/piece_move.wav");

    if (move_piece_sfx_ == nullptr)
    {
        std::cerr << "Failed to load sfx=" << Mix_GetError();
        return EXIT_FAILURE;
    }

    std::cout << "Move piece SFX loaded...\n";

    // TODO
    // Textures to constructor
    auto black_king = std::make_shared<King>(PieceColor::Black, renderer_, "images/b_king_png_shadow_1024px.png");
    auto black_queen = std::make_shared<Queen>(PieceColor::Black, renderer_, "images/b_queen_png_shadow_1024px.png");
    auto black_rook = std::make_shared<Rook>(PieceColor::Black, renderer_, "images/b_rook_png_shadow_1024px.png");
    auto black_bishop = std::make_shared<Bishop>(PieceColor::Black, renderer_, "images/b_bishop_png_shadow_1024px.png");
    auto black_knight = std::make_shared<Knight>(PieceColor::Black, renderer_, "images/b_knight_png_shadow_1024px.png");
    auto black_pawn = std::make_shared<Pawn>(PieceColor::Black, renderer_, "images/b_pawn_png_shadow_1024px.png");

    auto white_king = std::make_shared<King>(PieceColor::White, renderer_, "images/w_king_png_shadow_1024px.png");
    auto white_queen = std::make_shared<Queen>(PieceColor::White, renderer_, "images/w_queen_png_shadow_1024px.png");
    auto white_rook = std::make_shared<Rook>(PieceColor::White, renderer_, "images/w_rook_png_shadow_1024px.png");
    auto white_bishop = std::make_shared<Bishop>(PieceColor::White, renderer_, "images/w_bishop_png_shadow_1024px.png");
    auto white_knight = std::make_shared<Knight>(PieceColor::White, renderer_, "images/w_knight_png_shadow_1024px.png");
    auto white_pawn = std::make_shared<Pawn>(PieceColor::White, renderer_, "images/w_pawn_png_shadow_1024px.png");

    board_ =
    {
        { black_rook, black_knight, black_bishop, black_queen, black_king, black_bishop, black_knight, black_rook },
        { black_pawn, black_pawn, black_pawn, black_pawn, black_pawn, black_pawn, black_pawn, black_pawn },
        { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
        { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
        { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
        { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
        { white_pawn, white_pawn, white_pawn, white_pawn, white_pawn, white_pawn, white_pawn, white_pawn },
        { white_rook, white_knight, white_bishop, white_queen, white_king, white_bishop, white_knight, white_rook }
    };

    std::cout << "Board prepared...\n";

    is_running_ = true;
    std::cout << "Initialization finished.\n";

    return true;
}

void Game::startLoop()
{
    // TODO remove???
}

void Game::handleEvents()
{
    SDL_Event e;
    int error = 0;

    auto old_column_index = 0;
    auto old_row_index = 0;

    auto new_column_index = 0;
    auto new_row_index = 0;

    while (SDL_PollEvent(&e)) {

        if (e.type == SDL_QUIT)
        {
            std::cout << "Window closed, quitting...\n";
            is_running_ = false;
        }

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
        {
            std::cout << "ESC pressed, quitting...\n";
            is_running_ = false;
        }

        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                old_column_index = e.button.x / POSITION_WIDTH;
                old_row_index = e.button.y / POSITION_HEIGHT;
                std::cout << "old=[" << old_column_index << ", " << old_row_index << "]" << '\n';
            }
        }

        if (e.type == SDL_MOUSEBUTTONUP)
        {
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                new_column_index = e.button.x / POSITION_WIDTH;
                new_row_index = e.button.y / POSITION_HEIGHT;
                std::cout << "new= [" << new_column_index << ", " << new_row_index << "]" << '\n';

                if (CanMove(old_column_index, old_row_index, new_column_index, new_row_index))
                {
                    // Move piece
                    board_[new_row_index][new_column_index] = std::move(board_[old_row_index][old_column_index]);

                    error = Mix_PlayChannel(SOUND_PLAY_CHANNEL, move_piece_sfx_, SOUND_NO_REPEAT);

                    if (error == SOUND_ERROR)
                    {
                        throw std::runtime_error(Mix_GetError());
                    }
                }
            }
        }

        std::cout << std::flush;
    }
}

void Game::update()
{
    int error = 0;

//    SDL_Event e;
//    bool quit = false;

    while (is_running_) {
//        while (SDL_PollEvent(&e)) {

//            if (e.type == SDL_QUIT)
//            {
//                std::cout << "Window closed, quitting...\n";
//                quit = true;
//            }

//            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
//            {
//                std::cout << "ESC pressed, quitting...\n";
//                quit = true;
//            }

//            if (e.type == SDL_MOUSEBUTTONDOWN)
//            {
//                if (e.button.button == SDL_BUTTON_LEFT)
//                {
//                    old_column_index = e.button.x / POSITION_WIDTH;
//                    old_row_index = e.button.y / POSITION_HEIGHT;
//                    std::cout << "old=[" << old_column_index << ", " << old_row_index << "]" << '\n';
//                }
//            }

//            if (e.type == SDL_MOUSEBUTTONUP)
//            {
//                if (e.button.button == SDL_BUTTON_LEFT)
//                {
//                    new_column_index = e.button.x / POSITION_WIDTH;
//                    new_row_index = e.button.y / POSITION_HEIGHT;
//                    std::cout << "new= [" << new_column_index << ", " << new_row_index << "]" << '\n';

//                    if (CanMove(old_column_index, old_row_index, new_column_index, new_row_index))
//                    {
//                        // Move piece
//                        board_[new_row_index][new_column_index] = std::move(board_[old_row_index][old_column_index]);

//                        error = Mix_PlayChannel(SOUND_PLAY_CHANNEL, move_piece_sfx_, SOUND_NO_REPEAT);

//                        if (error == SOUND_ERROR)
//                        {
//                            throw std::runtime_error(Mix_GetError());
//                        }
//                    }
//                }
//            }

//            std::cout << std::flush;
//        }

        handleEvents();

        SDL_Rect rectangle;

        // Render chess board
        for (auto column = 0; column < BOARD_WIDTH; column++)
        {
            for (auto row = 0; row < BOARD_HEIGHT; row++)
            {
                rectangle.x = column * POSITION_WIDTH;
                rectangle.y = row * POSITION_HEIGHT;
                rectangle.h = POSITION_HEIGHT;
                rectangle.w = POSITION_WIDTH;

                // Piece background
                if ((column + row) % 2 == 0)
                {
                    // Light
                    error = SDL_SetRenderDrawColor(renderer_, BOARD_COLOR_LIGHT_R, BOARD_COLOR_LIGHT_G, BOARD_COLOR_LIGHT_B, ALPHA_COLOR);
                }
                else
                {
                    // Dark
                    error = SDL_SetRenderDrawColor(renderer_, BOARD_COLOR_DARK_R, BOARD_COLOR_DARK_G, BOARD_COLOR_DARK_B, ALPHA_COLOR);
                }

                if (error)
                {
                    throw std::runtime_error(SDL_GetError());
                }

                error = SDL_RenderFillRect(renderer_, &rectangle);

                if (error)
                {
                    throw std::runtime_error(SDL_GetError());
                }

                // Piece
                const auto& piece = board_[row][column];
                if (piece != nullptr)
                {
                    error = SDL_RenderCopy(renderer_, piece->GetTexture(), nullptr, &rectangle);

                    if (error)
                    {
                        throw std::runtime_error(SDL_GetError());
                    }
                }
            }
        }

        // Render frame
        SDL_RenderPresent(renderer_);
    }
}

void Game::render()
{
    SDL_RenderClear(renderer_);

    // TODO

    SDL_RenderPresent(renderer_);
}

void Game::destroyEverything()
{
    // Destroy resources
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    Mix_FreeChunk(move_piece_sfx_);

    // Close all the systems of SDL initialized at the top
    SDL_Quit();
    Mix_Quit();
    IMG_Quit();
}

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
