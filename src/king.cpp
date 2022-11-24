#include "king.hpp"

King::King(PieceColor piece_color)
    : Piece(PieceType::King, piece_color)
{

}

King::King(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::King, piece_color, renderer, texture_filename)
{

}

std::vector<Position> King::LegalMoves() const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    for (auto column = position.column - 1; column <= position.column + 1; column++)
    {
        for (auto row = position.row - 1; row <= position.row + 1; row++)
        {
            // Do not add current position of king
            if (column == position.column && row == position.row)
            {
                continue;
            }

            // Remove positions outside board
            if (column < 0 || column >= BOARD_WIDTH || row < 0 || row >= BOARD_HEIGHT)
            {
                continue;
            }

            legal_moves.emplace_back(column, row);
        }
    }

    return legal_moves;
}
