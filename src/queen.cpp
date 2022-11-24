#include "queen.hpp"

Queen::Queen(PieceColor piece_color)
    : Piece(PieceType::Queen, piece_color)
{

}

Queen::Queen(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Queen, piece_color, renderer, texture_filename)
{

}

std::vector<Position> Queen::GetLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return GetPseudoLegalMoves(board);
}

std::vector<Position> Queen::GetPseudoLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> pseudo_legal_moves;
    std::vector<Position> output;
    const auto& position = GetPosition();

    pseudo_legal_moves.emplace_back(Position(position.column, position.row + 1));

    for (auto column = 0; column < BOARD_WIDTH; column++)
    {
        for (auto row = 0; row < BOARD_HEIGHT; row++)
        {
            // diagonals TODO


            // vertical
            if (row == position.row)
            {
                pseudo_legal_moves.emplace_back(Position(column, row));
            }

            // horizontal
            if (column == position.column)
            {
                pseudo_legal_moves.emplace_back(Position(column, row));
            }
        }
    }
    
    // Filter invalid positions // TODO move to function
    std::copy_if(pseudo_legal_moves.begin(), pseudo_legal_moves.end(), std::back_inserter(output), [&](const Position& position)
        {
            // Remove invalid positions
            if (position.column >= BOARD_WIDTH || position.column < 0 || position.row >= BOARD_HEIGHT || position.row < 0)
            {
                return false;
            }

            // Remove ally positions
            const auto& piece_at_position = board[position.row][position.column];
            if (piece_at_position != nullptr && piece_at_position->GetPieceColor() == GetPieceColor())
            {
                return false;
            }

            return true;
        });

    return output;
}
