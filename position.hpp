#pragma once

#include "libs.hpp"

struct Position
{
    int x;
    int y;

    Position();
    Position(int x, int y);

    bool operator==(const Position& position) const;
    bool operator!=(const Position& position) const;

    bool isDefined() const;
    string ToString() const;
};
