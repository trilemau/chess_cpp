#include "king.hpp"

King::King()
    : Piece(PieceType::King)
{

}

King::King(SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::King, renderer, texture_filename)
{

}

std::vector<Position> King::LegalMoves() const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    for (auto x = position.x - 1; x <= position.x + 1; x++)
    {
        for (auto y = position.y - 1; y <= position.y + 1; y++)
        {
            // Do not add current position of king
            if (x == position.x && y == position.y)
            {
                continue;
            }

            // Remove positions outside board
            if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT)
            {
                continue;
            }

            legal_moves.emplace_back(x, y);
        }
    }

    return legal_moves;
}
