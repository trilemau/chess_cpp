#include "king.hpp"

King::King(PieceColor piece_color)
    : Piece(PieceType::King, piece_color)
{

}

King::King(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::King, piece_color, renderer, texture_filename)
{

}

std::vector<Position> King::GetLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    auto pseudo_legal_moves = GetPseudoLegalMoves(board);
    const auto& position = GetPosition();

    // TODO checkMATES
    // TODO castling

    return GetPseudoLegalMoves(board);
}

std::vector<Position> King::GetPseudoLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> pseudo_legal_moves;
    std::vector<Position> output;
    const auto& position = GetPosition();

    // Top
    pseudo_legal_moves.emplace_back(Position(position.column - 1, position.row - 1));
    pseudo_legal_moves.emplace_back(Position(position.column, position.row - 1));
    pseudo_legal_moves.emplace_back(Position(position.column + 1, position.row - 1));

    // Middle
    pseudo_legal_moves.emplace_back(Position(position.column - 1, position.row));
    pseudo_legal_moves.emplace_back(Position(position.column + 1, position.row));

    // Bottom
    pseudo_legal_moves.emplace_back(Position(position.column - 1, position.row + 1));
    pseudo_legal_moves.emplace_back(Position(position.column, position.row + 1));
    pseudo_legal_moves.emplace_back(Position(position.column + 1, position.row + 1));

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

