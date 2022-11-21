#pragma once

#include "piece.hpp"

class Knight : public Piece
{
public:
	Knight();
	Knight(SDL_Renderer* renderer, const string& texture_filename);

	std::vector<Position> LegalMoves() const override;
};