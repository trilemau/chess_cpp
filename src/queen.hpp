#pragma once

#include "piece.hpp"

class Queen : public Piece
{
public:
	Queen(PieceColor piece_color);
	Queen(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename);

	std::vector<Position> LegalMoves() const override;
};