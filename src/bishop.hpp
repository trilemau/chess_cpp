#pragma once

#include "piece.hpp"

class Bishop : public Piece
{
public:
	Bishop();
	Bishop(SDL_Renderer* renderer, const string& texture_filename);

	std::vector<Position> LegalMoves() const override;
};