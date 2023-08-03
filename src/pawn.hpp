#pragma once

#include "piece.hpp"

class Pawn : public Piece
{
	bool has_moved_;

public:
	Pawn(PieceColor piece_color);
	Pawn(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename);

	std::vector<Position> GetLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const override;
	std::vector<Position> GetPseudoLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const override;
    std::vector<Position> GetAttackingMoves(const vector<vector<shared_ptr<Piece>>>& board) const override;
};
