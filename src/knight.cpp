#include "knight.hpp"

Knight::Knight(PieceColor piece_color)
    : Piece(PieceType::Knight, piece_color)
{

}

Knight::Knight(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Knight, piece_color, renderer, texture_filename)
{

}

std::vector<Position> Knight::GetLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return GetPseudoLegalMoves(board);
}

std::vector<Position> Knight::GetPseudoLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> pseudo_legal_moves;
    std::vector<Position> output;
    const auto& position = GetPosition();

    const auto column = position.column;
    const auto row = position.row;

    // TODO refactor

    pseudo_legal_moves.emplace_back(Position(column - 1, row - 2));
    pseudo_legal_moves.emplace_back(Position(column + 1, row - 2));
    pseudo_legal_moves.emplace_back(Position(column - 2, row - 1));
    pseudo_legal_moves.emplace_back(Position(column + 2, row - 1));
    pseudo_legal_moves.emplace_back(Position(column - 2, row + 1));
    pseudo_legal_moves.emplace_back(Position(column + 2, row + 1));
    pseudo_legal_moves.emplace_back(Position(column - 1, row + 2));
    pseudo_legal_moves.emplace_back(Position(column + 1, row + 2));

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

std::vector<Position> Knight::GetAttackingMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> output;

    return output;
}
