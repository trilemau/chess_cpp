#pragma once

#include "libs.hpp"

#include "position.hpp"

class Piece
{
    SDL_Texture* texture_;
    bool initialized_;

protected:
    PieceType type_;
    Position position_;

public:
    Piece();
    Piece(SDL_Renderer* renderer, string_view texture_filename);
    virtual ~Piece();

    void SetPosition(const Position& position);

    virtual std::vector<Position> LegalMoves() const = 0;
};

class King : public Piece
{
public:
    King();
    King(SDL_Renderer* renderer, string_view texture_filename);

    std::vector<Position> LegalMoves() const override;
};
