#include "bishop.hpp"

Bishop::Bishop(PieceColor piece_color)
    : Piece(PieceType::Bishop, piece_color)
{

}

Bishop::Bishop(PieceColor piece_color,SDL_Renderer* renderer, const string& texture_filename)
    : Piece(PieceType::Bishop, piece_color, renderer, texture_filename)
{

}

std::vector<Position> Bishop::GetLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> legal_moves;
    const auto& position = GetPosition();

    // TODO

    return GetPseudoLegalMoves(board);
}

std::vector<Position> Bishop::GetPseudoLegalMoves(const vector<vector<shared_ptr<Piece>>>& board) const
{
    std::vector<Position> pseudo_legal_moves;
    std::vector<Position> output;
    const auto& position = GetPosition();

    auto column = position.column;
    auto row = position.row;

    // TODO refactor

    // diagonal "/" down to up
    while (row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH)
    {
        column++;
        row--;

        if (row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH && board[row][column])
        {
            if (board[row][column] && GetPieceColor() != board[row][column]->GetPieceColor())
            {
                pseudo_legal_moves.emplace_back(Position(column, row));
            }

            break;
        }

        pseudo_legal_moves.emplace_back(Position(column, row));
    }

    column = position.column;
    row = position.row;

    // diagonal "/" up to down
    while (row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH)
    {
        column--;
        row++;

        if (row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH && board[row][column])
        {
            if (board[row][column] && GetPieceColor() != board[row][column]->GetPieceColor())
            {
                pseudo_legal_moves.emplace_back(Position(column, row));
            }

            break;
        }

        pseudo_legal_moves.emplace_back(Position(column, row));
    }

    column = position.column;
    row = position.row;

    // diagonal "\" down to up
    while (row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH)
    {
        column++;
        row++;

        if (row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH && board[row][column])
        {
            if (board[row][column] && GetPieceColor() != board[row][column]->GetPieceColor())
            {
                pseudo_legal_moves.emplace_back(Position(column, row));
            }

            break;
        }

        pseudo_legal_moves.emplace_back(Position(column, row));
    }

    column = position.column;
    row = position.row;

    // diagonal "\" up to down
    while (row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH)
    {
        column--;
        row--;

        if (row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH && board[row][column])
        {
            if (board[row][column] && GetPieceColor() != board[row][column]->GetPieceColor())
            {
                pseudo_legal_moves.emplace_back(Position(column, row));
            }

            break;
        }

        pseudo_legal_moves.emplace_back(Position(column, row));
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
