#include "king.hpp"

#include <unordered_set>

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
    const auto pseudo_legal_moves = GetPseudoLegalMoves(board);
    std::vector<Position> legal_moves;

    std::unordered_set<Position, PositionHash> enemy_positions;

    for (auto column = 0; column < BOARD_WIDTH; column++)
    {
        for (auto row = 0; row < BOARD_HEIGHT; row++)
        {
            const auto& piece = board[row][column];

            // Skip if piece is empty
            if (piece == nullptr)
            {
                continue;
            }

            // Skip if piece is not an enemy
            if (GetPieceColor() == piece->GetPieceColor())
            {
                continue;
            }

            const auto enemy_moves = piece->GetPseudoLegalMoves(board);

            for (const auto& enemy_move : enemy_moves)
            {
                enemy_positions.emplace(enemy_move);
            }
        }
    }

    // Avoid positons where king is attacked from enemy
    std::copy_if(pseudo_legal_moves.begin(), pseudo_legal_moves.end(), std::back_inserter(legal_moves), [&](const Position& position)
        {
            return enemy_positions.find(position) == enemy_positions.end();
        });

    // TODO checkMATES
    // TODO castling

    return legal_moves;
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

std::vector<Position> King::GetAttackingMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> output;

    return output;
}
