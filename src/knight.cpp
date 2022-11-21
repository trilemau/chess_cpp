#include "knight.hpp"

Knight::Knight()
    : Piece(PieceType::Knight)
{

}

Knight::Knight(SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Knight, renderer, texture_filename)
{

}

std::vector<Position> Knight::LegalMoves() const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return legal_moves;
}
