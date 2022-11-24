#include "pawn.hpp"

Pawn::Pawn(PieceColor piece_color)
    : Piece(PieceType::Pawn, piece_color)
    , has_moved_(false)
{

}

Pawn::Pawn(PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Pawn, piece_color, renderer, texture_filename)
    , has_moved_(false)
{

}

std::vector<Position> Pawn::GetLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return GetPseudoLegalMoves(board);
}

std::vector<Position> Pawn::GetPseudoLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    // Invert values depending on White or Black
    auto invert = GetPieceColor() == PieceColor::White ? -1 : 1;
    const auto& position = GetPosition();

    // No moves if piece in front of pawn
    if (board[position.row + 1 * invert][position.column] != nullptr)
    {
        return {};
    }

    std::vector<Position> pseudo_legal_moves;
    std::vector<Position> output;

    pseudo_legal_moves.emplace_back(Position(position.column, position.row + 1 * invert));

    // Only if pawn have not moved
    if (has_moved_ == false)
    {
        pseudo_legal_moves.emplace_back(Position(position.column, position.row + 2 * invert));
    }

    // TODO only one move after first move
    // TODO add en passant
    // TODO promotion

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

