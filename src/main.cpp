#include "libs.hpp"

#include "game.hpp"

#include "renderer.hpp"

#include "king.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "pawn.hpp"

int main()
{
    /*
    std::cout << "Game started...\n";

    SDL_Init(SDL_INIT_EVERYTHING);

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

//    //Set the draw color of renderer to black
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

//    //Clear the renderer with the draw color
//    SDL_RenderClear(renderer);

//    //Update the renderer which will show the renderer cleared by the draw color
//    SDL_RenderPresent(renderer);

    // TODO
    // Renderer to singleton 
    // Textures to constructor
    auto black_king = std::make_shared<King>(PieceColor::Black, renderer, "images/b_king_png_shadow_1024px.png");
    auto black_queen = std::make_shared<Queen>(PieceColor::Black, renderer, "images/b_queen_png_shadow_1024px.png");
    auto black_rook = std::make_shared<Rook>(PieceColor::Black, renderer, "images/b_rook_png_shadow_1024px.png");
    auto black_bishop = std::make_shared<Bishop>(PieceColor::Black, renderer, "images/b_bishop_png_shadow_1024px.png");
    auto black_knight = std::make_shared<Knight>(PieceColor::Black, renderer, "images/b_knight_png_shadow_1024px.png");
    auto black_pawn = std::make_shared<Pawn>(PieceColor::Black, renderer, "images/b_pawn_png_shadow_1024px.png");

    auto white_king = std::make_shared<King>(PieceColor::White, renderer, "images/w_king_png_shadow_1024px.png");
    auto white_queen = std::make_shared<Queen>(PieceColor::White, renderer, "images/w_queen_png_shadow_1024px.png");
    auto white_rook = std::make_shared<Rook>(PieceColor::White, renderer, "images/w_rook_png_shadow_1024px.png");
    auto white_bishop = std::make_shared<Bishop>(PieceColor::White, renderer, "images/w_bishop_png_shadow_1024px.png");
    auto white_knight = std::make_shared<Knight>(PieceColor::White, renderer, "images/w_knight_png_shadow_1024px.png");
    auto white_pawn = std::make_shared<Pawn>(PieceColor::White, renderer, "images/w_pawn_png_shadow_1024px.png");

    // Initialize audio
    if (Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, SOUND_CHANNELS, SOUND_CHUNKS) != SDL_NO_ERROR)
    {
        std::cerr << "Failed to initialize audio=" << Mix_GetError();
        return EXIT_FAILURE;
    }

    Mix_Chunk* piece_move_sfx = Mix_LoadWAV("sounds/piece_move.wav");

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
        { white_rook, white_knight, white_bishop, white_queen, white_king, white_bishop, white_knight, white_rook }
    };

    set<shared_ptr<Piece>> p1_pieces;
    set<shared_ptr<Piece>> p2_pieces;

    SDL_Event e;
    int error = 0;
    bool quit = false;

    auto old_column_index = 0;
    auto old_row_index = 0;

    auto new_column_index = 0;
    auto new_row_index = 0;

    try
    {
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
                            board[new_row_index][new_column_index] = std::move(board[old_row_index][old_column_index]);

                            Mix_PlayChannel(SOUND_PLAY_CHANNEL, piece_move_sfx, SOUND_NO_REPEAT);
                        }
                    }
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

    // Destroy audio sfx
    Mix_FreeChunk(piece_move_sfx);

    // Destroy the window created above
    SDL_DestroyWindow(window);

    // Close all the systems of SDL initialized at the top
    SDL_Quit();
    Mix_Quit();
    IMG_Quit();
    */

    Game game;
    game.initialize();

    try {
        game.update();
    } catch (const std::exception& exception) {
        std::cerr << "Unexpected exception=" << exception.what() << '\n';
    }

    return EXIT_SUCCESS;
}
