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

    // TODO use Position.class
    int old_column_index = 0;
    int old_row_index = 0;

public:
    Game();
    ~Game();

//    void foo() { SDL_Init(SDL_INIT_EVERYTHING); }

    // TODO move to private methods
    bool isRunning() const;
    bool initialize();
    void handleEvents();
    void update();
    void renderBoard();
    void destroyEverything();

    const auto& getBoard() const;
    auto& getBoard();

    const Piece& GetPiece(const Position& position) const;
    Piece& GetPiece(const Position& position);

    const Position& GetCurrentPosition() const;
    Position& GetCurrentPosition();
};
