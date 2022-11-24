#include "rook.hpp"

Rook::Rook(PieceColor piece_color)
    : Piece(PieceType::Rook, piece_color)
{

}

Rook::Rook(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Rook, piece_color, renderer, texture_filename)
{

}

std::vector<Position> Rook::GetLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return legal_moves;
}

std::vector<Position> Rook::GetPseudoLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return legal_moves;
}
