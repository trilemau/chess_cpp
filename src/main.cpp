#include "libs.hpp"

#include "renderer.hpp"

#include "king.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "pawn.hpp"

#define BOARD_COLOR_LIGHT_R 124
#define BOARD_COLOR_LIGHT_G 76
#define BOARD_COLOR_LIGHT_B 62

#define BOARD_COLOR_DARK_R 81
#define BOARD_COLOR_DARK_G 42
#define BOARD_COLOR_DARK_B 42

#define ALPHA_COLOR 255

#define SDL_NO_ERROR 0

int main()
{
    std::cout << "Game started...\n";

    //Initialize all the systems of SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    //Create a window with a title, "Getting Started", in the centre
    //(or undefined x and y positions), with dimensions of 800 px width
    //and 600 px height and force it to be shown on screen
    SDL_Window* window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::cerr << "Failed to initialize window=" << SDL_GetError();
        return EXIT_FAILURE;
    }

    //Create a renderer for the window created above, with the first display driver present
    //and with no additional settings
    Renderer renderer_wrapper(window);
    SDL_Renderer* renderer = renderer_wrapper.GetRenderer();

    //Set the draw color of renderer to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //Clear the renderer with the draw color
    SDL_RenderClear(renderer);

    //Update the renderer which will show the renderer cleared by the draw color
    SDL_RenderPresent(renderer);

    auto black_king = std::make_shared<King>(renderer, "images/b_king_png_shadow_1024px.png");
    auto black_queen = std::make_shared<Queen>(renderer, "images/b_queen_png_shadow_1024px.png");
    auto black_rook = std::make_shared<Rook>(renderer, "images/b_rook_png_shadow_1024px.png");
    auto black_bishop = std::make_shared<Bishop>(renderer, "images/b_bishop_png_shadow_1024px.png");
    auto black_knight = std::make_shared<Knight>(renderer, "images/b_knight_png_shadow_1024px.png");
    auto black_pawn = std::make_shared<Pawn>(renderer, "images/b_pawn_png_shadow_1024px.png");

    auto white_king = std::make_shared<King>(renderer, "images/w_king_png_shadow_1024px.png");
    auto white_queen = std::make_shared<Queen>(renderer, "images/w_queen_png_shadow_1024px.png");
    auto white_rook = std::make_shared<Rook>(renderer, "images/w_rook_png_shadow_1024px.png");
    auto white_bishop = std::make_shared<Bishop>(renderer, "images/w_bishop_png_shadow_1024px.png");
    auto white_knight = std::make_shared<Knight>(renderer, "images/w_knight_png_shadow_1024px.png");
    auto white_pawn = std::make_shared<Pawn>(renderer, "images/w_pawn_png_shadow_1024px.png");

    auto texture = IMG_LoadTexture(renderer, "images/w_king_png_shadow_1024px.png");

    // Initialize audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != SDL_NO_ERROR) // TODO values to macro
    {
        std::cerr << "Failed to initialize audio=" << Mix_GetError();
        return EXIT_FAILURE;
    }

    Mix_Music* piece_move_sfx = Mix_LoadMUS("sounds/piece_move.mp3");

    if (piece_move_sfx == nullptr)
    {
        std::cerr << "Failed to load sfx=" << Mix_GetError();
        return EXIT_FAILURE;
    }

    vector<vector<shared_ptr<Piece>>> board
    {
        { black_rook, black_knight, black_bishop, black_queen, black_king, black_bishop, black_knight, black_rook },
        { black_pawn, black_pawn, black_pawn, black_pawn, black_pawn, black_pawn, black_pawn, black_pawn },
        { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
        { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
        { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
        { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
        { white_pawn, white_pawn, white_pawn, white_pawn, white_pawn, white_pawn, white_pawn, white_pawn },
        { black_rook, white_knight, black_bishop, white_queen, white_king, black_bishop, white_knight, black_rook }
    };

    try
    {
        SDL_Event e;
        int error = 0;
        bool quit = false;
        while (!quit) {
            while (SDL_PollEvent(&e)) {

                if (e.type == SDL_QUIT)
                {
                    std::cout << "Window closed, quitting...\n";
                    quit = true;
                }

                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                {
                    std::cout << "ESC pressed, quitting...\n";
                    quit = true;
                }

                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    std::cout << "mouse button pressed\n";
                }

                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    Mix_PlayMusic(piece_move_sfx, 0); // TODO to macro

                    std::cout << "mouse button released\n";
                }

                std::cout << std::flush;
            }

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
                        error = SDL_SetRenderDrawColor(renderer, BOARD_COLOR_LIGHT_R, BOARD_COLOR_LIGHT_G, BOARD_COLOR_LIGHT_B, ALPHA_COLOR);
                    }
                    else
                    {
                        // Dark
                        error = SDL_SetRenderDrawColor(renderer, BOARD_COLOR_DARK_R, BOARD_COLOR_DARK_G, BOARD_COLOR_DARK_B, ALPHA_COLOR);
                    }

                    if (error)
                    {
                        throw std::runtime_error(SDL_GetError());
                    }

                    error = SDL_RenderFillRect(renderer, &rectangle);

                    if (error)
                    {
                        throw std::runtime_error(SDL_GetError());
                    }

                    // Piece
                    const auto& piece = board[row][column];
                    if (piece != nullptr)
                    {
                        error = SDL_RenderCopy(renderer, piece->GetTexture(), nullptr, &rectangle);

                        if (error)
                        {
                            throw std::runtime_error(SDL_GetError());
                        }
                    }
                }
            }

            // Render frame
            SDL_RenderPresent(renderer);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unexpected exception=" << e.what() << '\n';
    }

    // Destroy audio
    Mix_FreeMusic(piece_move_sfx);

    // Destroy the window created above
    SDL_DestroyWindow(window);

    // Close all the systems of SDL initialized at the top
    SDL_Quit();
    Mix_Quit();
    IMG_Quit();

    return EXIT_SUCCESS;
}
