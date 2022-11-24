#pragma once

#include "libs.hpp"

#include "position.hpp"

class Piece;
struct Position;


class Game
{
    bool testing_;
    bool is_running_;

    SDL_Window* window_;
    SDL_Renderer* renderer_;
    Mix_Chunk* move_piece_sfx_;

    set<shared_ptr<Piece>> captured_pieces_player1; // TODO implement captured pieces
    set<shared_ptr<Piece>> captured_pieces_player2;

    shared_ptr<Piece> selected_piece_;

    vector<vector<shared_ptr<Piece>>> board_;
    bool castle_king_side_;
    bool castle_queen_side_;

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

    const vector<vector<shared_ptr<Piece>>>& GetBoard() const;
    vector<vector<shared_ptr<Piece>>>& GetBoard();

    const Piece& GetPiece(const Position& position) const;
    Piece& GetPiece(const Position& position);

private:
    shared_ptr<Piece> createPieceFromChar(char c) const;
    shared_ptr<Piece> createPieceFromCharNoTexture(char c) const;
    int getIntFromChar(char c) const;
};
