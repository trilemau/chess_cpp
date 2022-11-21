#pragma once

#include "piece.hpp"

class Queen : public Piece
{
public:
	Queen();
	Queen(SDL_Renderer* renderer, const string& texture_filename);

	std::vector<Position> LegalMoves() const override;
};