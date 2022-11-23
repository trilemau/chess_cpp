#pragma once

#include "piece.hpp"

class Knight : public Piece
{
public:
	Knight(PieceColor piece_color);
	Knight(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename);

	std::vector<Position> LegalMoves() const override;
};