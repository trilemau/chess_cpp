#pragma once

#include "libs.hpp"

#include "position.hpp"

class Piece;
class Position;

typedef vector<vector<shared_ptr<Piece>>> ChessBoard;

class Game
{
    bool testing_;
    bool is_running_;

    SDL_Window* window_;
    SDL_Renderer* renderer_;
    Mix_Chunk* move_piece_sfx_;

    set<shared_ptr<Piece>> pieces_player1;
    set<shared_ptr<Piece>> pieces_player2;

    set<shared_ptr<Piece>> captured_pieces_player1;
    set<shared_ptr<Piece>> captured_pieces_player2;

    shared_ptr<Piece> selected_piece_;
    Position mouse_position_;

    ChessBoard board_;
    Position current_position_;

    // TODO use Position.class
    int old_column_index = 0;
    int old_row_index = 0;

public:
    Game();
    ~Game();

    void SetTesting(bool testing);

    // TODO move to private methods

    bool Initialize();
    bool LoadBoard(const string& fen);
    void HandleEvents();
    void Update();
    void RenderBoard();
    void DestroyResources();

    void OnMousePressed(const SDL_Event& event);
    void OnMouseReleased(const SDL_Event& event);

    // States
    bool isRunning() const;

    const ChessBoard& GetBoard() const;
    ChessBoard& GetBoard();

    const Piece& GetPiece(const Position& position) const;
    Piece& GetPiece(const Position& position);

    const Position& GetCurrentPosition() const;
    Position& GetCurrentPosition();

private:
    shared_ptr<Piece> createPieceFromChar(char c) const;
    shared_ptr<Piece> createPieceFromCharNoTexture(char c) const;
    int getIntFromChar(char c) const;
};
