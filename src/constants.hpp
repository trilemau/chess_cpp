#pragma once

// TODO dont use macros

#define FEN_STARTING_BOARD "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

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

#define BLACK_KING_TEXTURE "images/b_king_png_shadow_1024px.png"
#define BLACK_QUEEN_TEXTURE "images/b_queen_png_shadow_1024px.png"
#define BLACK_ROOK_TEXTURE "images/b_rook_png_shadow_1024px.png"
#define BLACK_BISHOP_TEXTURE "images/b_bishop_png_shadow_1024px.png"
#define BLACK_KNIGHT_TEXTURE "images/b_knight_png_shadow_1024px.png"
#define BLACK_PAWN_TEXTURE "images/b_pawn_png_shadow_1024px.png"
#define WHITE_KING_TEXTURE "images/w_king_png_shadow_1024px.png"
#define WHITE_QUEEN_TEXTURE "images/w_queen_png_shadow_1024px.png"
#define WHITE_ROOK_TEXTURE "images/w_rook_png_shadow_1024px.png"
#define WHITE_BISHOP_TEXTURE "images/w_bishop_png_shadow_1024px.png"
#define WHITE_KNIGHT_TEXTURE "images/w_knight_png_shadow_1024px.png"
#define WHITE_PAWN_TEXTURE "images/w_pawn_png_shadow_1024px.png"

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
