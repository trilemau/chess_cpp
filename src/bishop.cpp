#include "bishop.hpp"

Bishop::Bishop()
    : Piece(PieceType::Bishop)
{

}

Bishop::Bishop(SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Bishop, renderer, texture_filename)
{

}

std::vector<Position> Bishop::LegalMoves() const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return legal_moves;
}
