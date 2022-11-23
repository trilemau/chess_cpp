#pragma once

#include "piece.hpp"

class King : public Piece
{
public:
    King(PieceColor piece_color);
    King(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename);

    std::vector<Position> LegalMoves() const override;
};
