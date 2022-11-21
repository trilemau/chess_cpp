#include "position.hpp"

Position::Position()
    : x(INVALID_VALUE)
    , y(INVALID_VALUE) {}

Position::Position(int x, int y)
    : x(x)
    , y(y) {}

bool Position::operator==(const Position &position) const
{
    return x == position.x && y == position.y;
};

bool Position::operator!=(const Position &position) const
{
    return !(*this == position);
};

bool Position::isDefined() const
{
    return x != INVALID_VALUE && y != INVALID_VALUE;
}

string Position::ToString() const
{
    return "{x=" + std::to_string(x) + ", y=" + std::to_string(y) + "}";
}
