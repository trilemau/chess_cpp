#include "queen.hpp"

Queen::Queen(PieceColor piece_color)
    : Piece(PieceType::Queen, piece_color)
{

}

Queen::Queen(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Queen, piece_color, renderer, texture_filename)
{

}

std::vector<Position> Queen::GetLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return legal_moves;
}

std::vector<Position> Queen::GetPseudoLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return legal_moves;
}
