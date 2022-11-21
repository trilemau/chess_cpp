#include "pawn.hpp"

Pawn::Pawn()
    : Piece(PieceType::Pawn)
{

}

Pawn::Pawn(SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Pawn, renderer, texture_filename)
{

}

std::vector<Position> Pawn::LegalMoves() const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return legal_moves;
}
