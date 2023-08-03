#pragma once

#include "piece.hpp"

class Bishop : public Piece
{
public:
	Bishop(PieceColor piece_color);
	Bishop(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename);

	std::vector<Position> GetLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const override;
	std::vector<Position> GetPseudoLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const override;
    std::vector<Position> GetAttackingMoves(const vector<vector<shared_ptr<Piece>>>& board) const override;
};
