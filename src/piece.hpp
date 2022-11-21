#pragma once

#include "libs.hpp"

#include "position.hpp"

class Piece
{
    PieceType piece_type_;
    Position position_;
    SDL_Texture* texture_;

public:
    Piece(PieceType piece_type);
    Piece(PieceType piece_type, SDL_Renderer* renderer, const string& texture_filename);
    virtual ~Piece();

    PieceType GetPieceType() const;

    const Position& GetPosition() const;
    void SetPosition(const Position& position);

    SDL_Texture* GetTexture();

    virtual std::vector<Position> LegalMoves() const = 0;
};
