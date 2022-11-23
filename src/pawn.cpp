#include "pawn.hpp"

Pawn::Pawn(PieceColor piece_color)
    : Piece(PieceType::Pawn, piece_color)
{

}

Pawn::Pawn(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Pawn, piece_color, renderer, texture_filename)
{

}

std::vector<Position> Pawn::LegalMoves() const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return legal_moves;
}
