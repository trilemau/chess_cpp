#include "rook.hpp"

Rook::Rook()
    : Piece(PieceType::Rook)
{

}

Rook::Rook(SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Rook, renderer, texture_filename)
{

}

std::vector<Position> Rook::LegalMoves() const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return legal_moves;
}
