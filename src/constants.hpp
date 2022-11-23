#pragma once

// TODO dont use macros

#define BOARD_COLOR_LIGHT_R 124
#define BOARD_COLOR_LIGHT_G 76
#define BOARD_COLOR_LIGHT_B 62

#define BOARD_COLOR_DARK_R 81
#define BOARD_COLOR_DARK_G 42
#define BOARD_COLOR_DARK_B 42

#define ALPHA_COLOR 255

#define SDL_NO_ERROR 0

#define SOUND_FREQUENCY 44100
#define SOUND_CHANNELS 2
#define SOUND_CHUNKS 2048
#define SOUND_NO_REPEAT 0
#define SOUND_PLAY_CHANNEL -1
#define SOUND_ERROR -1

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
