#include "knight.hpp"

Knight::Knight(PieceColor piece_color)
    : Piece(PieceType::Knight, piece_color)
{

}

Knight::Knight(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Knight, piece_color, renderer, texture_filename)
{

}

std::vector<Position> Knight::GetLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return legal_moves;
}

std::vector<Position> Knight::GetPseudoLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return legal_moves;
}

