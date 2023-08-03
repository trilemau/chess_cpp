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

size_t PositionHash::operator()(const Position& position) const
{
    // Combine the hash values of the member variables using bitwise XOR
    std::hash<int> hash;
    size_t hash_value = hash(position.column);

    hash_value ^= hash(position.row) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);

    return hash_value;
}
