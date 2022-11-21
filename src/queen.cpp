#include "queen.hpp"

Queen::Queen()
    : Piece(PieceType::Queen)
{

}

Queen::Queen(SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Queen, renderer, texture_filename)
{

}

std::vector<Position> Queen::LegalMoves() const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return legal_moves;
}
