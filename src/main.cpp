#include "libs.hpp"

#include "renderer.hpp"
#include "king.hpp"

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
    auto white_king = std::make_shared<King>(renderer, "images/w_king_png_shadow_1024px.png");

    vector<vector<shared_ptr<Piece>>> board
    {
        { black_king, black_king, black_king, black_king, black_king, black_king, black_king, black_king },
        { black_king, black_king, black_king, black_king, black_king, black_king, black_king, black_king },
        { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
        { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
        { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
        { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
        { white_king, white_king, white_king, white_king, white_king, white_king, white_king, white_king },
        { white_king, white_king, white_king, white_king, white_king, white_king, white_king, white_king }
    };

    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){

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
                    // White color
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                }
                else
                {
                    // Black color
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                }

                // Piece
                const auto& piece = board[row][column];
                if (piece != nullptr)
                {
                    SDL_RenderCopy(renderer, piece->GetTexture(), nullptr, &rectangle);
                }

                // Render chess board
                SDL_RenderFillRect(renderer, &rectangle);
            }
        }

        // Render frame
        SDL_RenderPresent(renderer);
    }

    // Destroy the window created above
    SDL_DestroyWindow(window);

    // Close all the systems of SDL initialized at the top
    SDL_Quit();

    return EXIT_SUCCESS;
}
