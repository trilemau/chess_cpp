#pragma once

#include "piece.hpp"

class Rook : public Piece
{
public:
	Rook();
	Rook(SDL_Renderer* renderer, const string& texture_filename);

	std::vector<Position> LegalMoves() const override;
};