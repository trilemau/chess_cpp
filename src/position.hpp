#pragma once

#include "libs.hpp"

struct Position
{
    int column;
    int row;

    Position(int column, int row);

    bool operator==(const Position& position) const;
    bool operator!=(const Position& position) const;

    string ToString() const;
};
