#include "bishop.hpp"

Bishop::Bishop(PieceColor piece_color)
    : Piece(PieceType::Bishop, piece_color)
{

}

Bishop::Bishop(PieceColor piece_color,SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Bishop, piece_color, renderer, texture_filename)
{

}

std::vector<Position> Bishop::LegalMoves() const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return legal_moves;
}
