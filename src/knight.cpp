#include "knight.hpp"

Knight::Knight(PieceColor piece_color)
    : Piece(PieceType::Knight, piece_color)
{

}

Knight::Knight(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Knight, piece_color, renderer, texture_filename)
{

}

std::vector<Position> Knight::LegalMoves() const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return legal_moves;
}
