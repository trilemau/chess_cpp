#pragma once

#include "piece.hpp"

class Pawn : public Piece
{
public:
	Pawn();
	Pawn(SDL_Renderer* renderer, const string& texture_filename);

	std::vector<Position> LegalMoves() const override;
};