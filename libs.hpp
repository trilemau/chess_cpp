#pragma once

// STD Libraries
#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <exception>

// Custom libraries
#include "enums.hpp"

// SDL
#include <SDL.h>
#include <SDL_image.h>

// Using ...
using std::string;
using std::string_view;
using std::array;
using std::vector;
using std::unique_ptr;

// cccheck todo seperate constant file
// Other constants

// WINDOW properties
constexpr const char* WINDOW_NAME = "Chess";
constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 640;

// Board size
constexpr int BOARD_HEIGHT = 8;
constexpr int BOARD_WIDTH = 8;

constexpr int POSITION_WIDTH = WINDOW_WIDTH / BOARD_WIDTH;
constexpr int POSITION_HEIGHT = WINDOW_HEIGHT / BOARD_HEIGHT;

constexpr int INVALID_VALUE = -1;

// Texture files
constexpr const char* BLACK_KING = "b_king_png_shadow_1024px.png";
