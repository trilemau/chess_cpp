#pragma once

#include "libs.hpp"

#include "position.hpp"

class Piece;
class Position;

class Game
{
    bool is_running_;

    SDL_Window* window_;
    SDL_Renderer* renderer_;
    Mix_Chunk* move_piece_sfx_;

    vector<vector<shared_ptr<Piece>>> board_;
    Position current_position_;

public:
    Game();
    ~Game();

    void foo() { SDL_Init(SDL_INIT_EVERYTHING); }

    bool isRunning() const;
//    void initialize();
//    void handleEvents();
    void update();
//    void render();
//    void destroyEverything();

    const auto& getBoard() const;
    auto& getBoard();

    const Piece& GetPiece(const Position& position) const;
    Piece& GetPiece(const Position& position);

    const Position& GetCurrentPosition() const;
    Position& GetCurrentPosition();
};
