#include "enums.hpp"

#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <exception>

// Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

// Screen size
constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 640;

// Board size
constexpr int BOARD_HEIGHT = 8;
constexpr int BOARD_WIDTH = 8;

constexpr int POSITION_HEIGHT = SCREEN_HEIGHT / BOARD_HEIGHT;
constexpr int POSITION_WIDTH = SCREEN_WIDTH / BOARD_WIDTH;

// Other constants
constexpr int INVALID_VALUE = -1;

using std::string;
using std::array;
using std::vector;
using std::unique_ptr;

struct Position
{
    int x = INVALID_VALUE;
    int y = INVALID_VALUE;
};

class Piece
{
    PieceType type_;
public:
    virtual std::vector<unique_ptr<Position>> LegalMoves(const Position& position) const = 0;

    virtual ~Piece() = 0;
};

class King : public Piece
{
public:
    std::vector<unique_ptr<Position>> LegalMoves(const Position& position) const override;

};

class Board
{
    array<array<unique_ptr<Piece>, BOARD_HEIGHT>, BOARD_HEIGHT> board_;
    Position current_position_;

public:
    const auto& getBoard() const
    {
        return board_;
    }

    auto& getBoard()
    {
        return board_;
    }

    const Piece& GetPiece(const Position& position) const
    {
        if (board_[position.x][position.y] == nullptr)
        {
            throw std::runtime_error("invalid position");
        }

        return *board_[position.x][position.y].get();
    }

    Piece& GetPiece(const Position& position)
    {
        if (board_[position.x][position.y] == nullptr)
        {
            throw std::runtime_error("invalid position");
        }

        return *board_[position.x][position.y].get();
    }

    const Position& GetCurrentPosition() const
    {
        return current_position_;
    }

    Position& GetCurrentPosition()
    {
        return current_position_;
    }
};

int main()
{
    std::cout << "hello\n";

    //Initialize all the systems of SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    //Create a window with a title, "Getting Started", in the centre
    //(or undefined x and y positions), with dimensions of 800 px width
    //and 600 px height and force it to be shown on screen
    SDL_Window* window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        return -1;
    }

    //Create a renderer for the window created above, with the first display driver present
    //and with no additional settings
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer == nullptr)
    {
        return -1;
    }

    //Set the draw color of renderer to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //Clear the renderer with the draw color
    SDL_RenderClear(renderer);

    //Update the renderer which will show the renderer cleared by the draw color which is green
    SDL_RenderPresent(renderer);

    SDL_Texture* texture;
    IMG_Init(IMG_INIT_PNG);
    texture = IMG_LoadTexture(renderer, "images/b_king_png_shadow_1024px.png");
    std::cout << SDL_GetError();

    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            std::cout << "1\n" << std::flush;

            if (e.type == SDL_QUIT){
                std::cout << "1\n";
            }
            if (e.type == SDL_KEYDOWN){
                std::cout << "1\n";
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                std::cout << "1\n" << std::flush;
            }
        }

        std::cout << "1\n" << std::flush;

        // cccheck should i fill bg here ?
        //Set the draw color of renderer to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        //Clear the renderer with the draw color
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Rect rectangle;
        for (auto x = 0; x < BOARD_WIDTH; x++)
        {
            for (auto y = 0; y < BOARD_HEIGHT; y++)
            {
                // draw white positions only - BG is already black
                if ((x + y) % 2 == 0)
                {
                    rectangle.x = x * POSITION_WIDTH;
                    rectangle.y = y * POSITION_HEIGHT;
                    rectangle.h = POSITION_HEIGHT;
                    rectangle.w = POSITION_WIDTH;
                    SDL_RenderFillRect(renderer, &rectangle);
                    SDL_RenderCopy(renderer, texture, nullptr, &rectangle);
                }
            }
        }

        // Render frame
        SDL_RenderPresent(renderer);
    }

    // Destroy the texture
//    SDL_DestroyTexture(texture);

    // Destroy the renderer created above
    SDL_DestroyRenderer(renderer);

    // Destroy the window created above
    SDL_DestroyWindow(window);

    // Close all the systems of SDL initialized at the top
    SDL_Quit();

    return 0;
}
