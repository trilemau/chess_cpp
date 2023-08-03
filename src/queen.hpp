#pragma once

#include "piece.hpp"

class Queen : public Piece
{
public:
	Queen(PieceColor piece_color);
	Queen(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename);

	std::vector<Position> GetLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const override;
	std::vector<Position> GetPseudoLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const override;
    std::vector<Position> GetAttackingMoves(const vector<vector<shared_ptr<Piece>>>& board) const override;
};
