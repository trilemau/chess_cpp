#include "position.hpp"

Position::Position(int column, int row)
    : column(column)
    , row(row) {}

bool Position::operator==(const Position &position) const
{
    return column == position.column && row == position.row;
};

bool Position::operator!=(const Position &position) const
{
    return !(*this == position);
};

string Position::ToString() const
{
    return "{column=" + std::to_string(column) + ", row=" + std::to_string(row) + "}";
}
