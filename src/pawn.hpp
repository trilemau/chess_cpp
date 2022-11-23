#pragma once

#include "piece.hpp"

class Pawn : public Piece
{
public:
	Pawn(PieceColor piece_color);
	Pawn(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename);

	std::vector<Position> LegalMoves() const override;
};