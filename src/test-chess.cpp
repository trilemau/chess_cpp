#include "catch.hpp"

#include "king.hpp"

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
    King king;

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
