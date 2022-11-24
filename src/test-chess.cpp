#include "catch.hpp"

#include "game.hpp"

#include "king.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "pawn.hpp"

void CompareMoves(const vector<Position>& moves, const vector<Position>& expected)
{
    if (moves.size() != expected.size())
    {
        INFO("Expected size = " << expected.size() << ", actual size = " << moves.size());
        REQUIRE(moves.size() == expected.size());
    }

    for (size_t i = 0; i < moves.size(); i++)
    {
        const auto& actual_move = moves[i];
        const auto& expected_move = expected[i];
        if (actual_move != expected_move)
        {
            INFO("Expected: " << expected_move.ToString() << ", actual: " << actual_move.ToString());
            REQUIRE(actual_move != expected_move);
        }
    }
}

TEST_CASE("King")
{
    King king(PieceColor::White);

    SECTION("Upper left board")
    {
        king.SetPosition({0, 0});
        std::vector<Position> expected = {
            {0, 1},
            {1, 0},
            {1, 1}
        };

        CompareMoves(king.LegalMoves(), expected);
    }

    SECTION("Upper middle board")
    {
        king.SetPosition({4, 0});
        std::vector<Position> expected = {
            {3, 0},
            {5, 0},
            {3, 1},
            {4, 1},
            {5, 1}
        };

        CompareMoves(king.LegalMoves(), expected);
    }

    SECTION("Upper right board")
    {
        king.SetPosition({7, 0});
        std::vector<Position> expected = {
            {6, 0},
            {6, 1},
            {7, 1}
        };

        CompareMoves(king.LegalMoves(), expected);
    }

    SECTION("Middle middle board")
    {
        king.SetPosition({4, 4});
        std::vector<Position> expected = {
            {3, 3},
            {4, 3},
            {5, 3},
            {3, 4},
            {5, 4},
            {3, 5},
            {4, 5},
            {5, 5}
        };

        CompareMoves(king.LegalMoves(), expected);
    }

    SECTION("Lower left board")
    {
        king.SetPosition({0, 7});
        std::vector<Position> expected = {
            {0, 6},
            {1, 6},
            {1, 7}
        };

        CompareMoves(king.LegalMoves(), expected);
    }

    SECTION("Lower middle board")
    {
        king.SetPosition({4, 7});
        std::vector<Position> expected = {
            {3, 6},
            {5, 6},
            {3, 7},
            {4, 7},
            {5, 7}
        };

        CompareMoves(king.LegalMoves(), expected);
    }

    SECTION("Lower right board")
    {
        king.SetPosition({7, 7});
        std::vector<Position> expected = {
            {6, 7},
            {6, 6},
            {7, 6}
        };

        CompareMoves(king.LegalMoves(), expected);
    }
}

TEST_CASE("Game.class")
{
    Game game;
    game.SetTesting(true);

    SECTION("Load FEN board")
    {
        REQUIRE(game.GetBoard().empty());

        REQUIRE_NOTHROW(game.LoadBoard(FEN_STARTING_BOARD));

        auto black_king = std::make_shared<King>(PieceColor::Black);
        auto black_queen = std::make_shared<Queen>(PieceColor::Black);
        auto black_rook_l = std::make_shared<Rook>(PieceColor::Black);
        auto black_rook_r = std::make_shared<Rook>(PieceColor::Black);
        auto black_bishop_l = std::make_shared<Bishop>(PieceColor::Black);
        auto black_bishop_r = std::make_shared<Bishop>(PieceColor::Black);
        auto black_knight_l = std::make_shared<Knight>(PieceColor::Black);
        auto black_knight_r = std::make_shared<Knight>(PieceColor::Black);
        auto black_pawn_1 = std::make_shared<Pawn>(PieceColor::Black);
        auto black_pawn_2 = std::make_shared<Pawn>(PieceColor::Black);
        auto black_pawn_3 = std::make_shared<Pawn>(PieceColor::Black);
        auto black_pawn_4 = std::make_shared<Pawn>(PieceColor::Black);
        auto black_pawn_5 = std::make_shared<Pawn>(PieceColor::Black);
        auto black_pawn_6 = std::make_shared<Pawn>(PieceColor::Black);
        auto black_pawn_7 = std::make_shared<Pawn>(PieceColor::Black);
        auto black_pawn_8 = std::make_shared<Pawn>(PieceColor::Black);

        black_king->SetPosition({ 0, 4 });
        black_queen->SetPosition({ 0, 3 });
        black_rook_l->SetPosition({ 0, 0 });
        black_rook_r->SetPosition({ 0, 7 });
        black_bishop_l->SetPosition({ 0, 2 });
        black_bishop_r->SetPosition({ 0, 5 });
        black_knight_l->SetPosition({ 0, 1 });
        black_knight_r->SetPosition({ 0, 6 });
        black_pawn_1->SetPosition({ 1, 0 });
        black_pawn_2->SetPosition({ 1, 1 });
        black_pawn_3->SetPosition({ 1, 2 });
        black_pawn_4->SetPosition({ 1, 3 });
        black_pawn_5->SetPosition({ 1, 4 });
        black_pawn_6->SetPosition({ 1, 5 });
        black_pawn_7->SetPosition({ 1, 6 });
        black_pawn_8->SetPosition({ 1, 7 });

        auto white_king = std::make_shared<King>(PieceColor::White);
        auto white_queen = std::make_shared<Queen>(PieceColor::White);
        auto white_rook_l = std::make_shared<Rook>(PieceColor::White);
        auto white_rook_r = std::make_shared<Rook>(PieceColor::White);
        auto white_bishop_l = std::make_shared<Bishop>(PieceColor::White);
        auto white_bishop_r = std::make_shared<Bishop>(PieceColor::White);
        auto white_knight_l = std::make_shared<Knight>(PieceColor::White);
        auto white_knight_r = std::make_shared<Knight>(PieceColor::White);
        auto white_pawn_1 = std::make_shared<Pawn>(PieceColor::White);
        auto white_pawn_2 = std::make_shared<Pawn>(PieceColor::White);
        auto white_pawn_3 = std::make_shared<Pawn>(PieceColor::White);
        auto white_pawn_4 = std::make_shared<Pawn>(PieceColor::White);
        auto white_pawn_5 = std::make_shared<Pawn>(PieceColor::White);
        auto white_pawn_6 = std::make_shared<Pawn>(PieceColor::White);
        auto white_pawn_7 = std::make_shared<Pawn>(PieceColor::White);
        auto white_pawn_8 = std::make_shared<Pawn>(PieceColor::White);

        white_king->SetPosition({ 7, 4 });
        white_queen->SetPosition({ 7, 3 });
        white_rook_l->SetPosition({ 7, 0 });
        white_rook_r->SetPosition({ 7, 7 });
        white_bishop_l->SetPosition({ 7, 2 });
        white_bishop_r->SetPosition({ 7, 5 });
        white_knight_l->SetPosition({ 7, 1 });
        white_knight_r->SetPosition({ 7, 6 });
        white_pawn_1->SetPosition({ 6, 0 });
        white_pawn_2->SetPosition({ 6, 1 });
        white_pawn_3->SetPosition({ 6, 2 });
        white_pawn_4->SetPosition({ 6, 3 });
        white_pawn_5->SetPosition({ 6, 4 });
        white_pawn_6->SetPosition({ 6, 5 });
        white_pawn_7->SetPosition({ 6, 6 });
        white_pawn_8->SetPosition({ 6, 7 });

        ChessBoard expected =
        {
            { black_rook_l, black_knight_l, black_bishop_l, black_queen, black_king, black_bishop_r, black_knight_r, black_rook_r },
            { black_pawn_1, black_pawn_2, black_pawn_3, black_pawn_4, black_pawn_5, black_pawn_6, black_pawn_7, black_pawn_8 },
            { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
            { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
            { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
            { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
            { white_pawn_1, white_pawn_2, white_pawn_3, white_pawn_4, white_pawn_5, white_pawn_6, white_pawn_7, white_pawn_8 },
            { white_rook_l, white_knight_l, white_bishop_l, white_queen, white_king, white_bishop_r, white_knight_r, white_rook_r }
        };

        const auto& result = game.GetBoard();

        REQUIRE(result.size() == expected.size());

        for (auto row_index = 0; row_index < result.size(); row_index++)
        {
            const auto& row1 = result[row_index];
            const auto& row2 = expected[row_index];

            REQUIRE(row1.size() == row2.size());

            for (auto column_index = 0; column_index < row1.size(); column_index++)
            {
                const auto& piece1 = row1[column_index];
                const auto& piece2 = row2[column_index];

                if (piece1 && piece2)
                {
                    const auto& position1 = piece1->GetPosition();
                    const auto& position2 = piece2->GetPosition();

                    INFO("row,col=[" + std::to_string(row_index) + ", " + std::to_string(column_index) + "]");
                    INFO("row,col=[" + std::to_string(row_index) + ", " + std::to_string(column_index) + "]");
                    INFO("position1=[" + std::to_string(position1.row) + ", " + std::to_string(position1.column) + "]");
                    INFO("position2=[" + std::to_string(position2.row) + ", " + std::to_string(position2.column) + "]");
                    
                    REQUIRE(*piece1 == *piece2);
                }
            }
        }
    }
}