#include "piece.hpp"

Piece::Piece()
    : initialized_(false) {}

Piece::Piece(SDL_Renderer* renderer, string_view texture_filename)
    : initialized_(false)
{
    IMG_Init(IMG_INIT_PNG);
    texture_ = IMG_LoadTexture(renderer, texture_filename.data());

    // Check if texture was loaded successfully
    if (texture_ == nullptr)
    {
        throw std::runtime_error("Failed to load piece texture");
    }

    initialized_ = false;
    std::cout << "Piece texture loaded successfully...\n";
}

Piece::~Piece()
{
    if (initialized_ == true)
    {
        SDL_DestroyTexture(texture_);
    }
}

void Piece::SetPosition(const Position &position)
{
    position_ = position;
}

King::King() {}

King::King(SDL_Renderer* renderer, string_view texture_filename)
    : Piece(renderer, texture_filename) {}

std::vector<Position> King::LegalMoves() const
{
    std::vector<Position> legal_moves;

    for (auto x = position_.x - 1; x <= position_.x + 1; x++)
    {
        for (auto y = position_.y - 1; y <= position_.y + 1; y++)
        {
            // Do not add current position of king
            if (x == position_.x && y == position_.y)
            {
                continue;
            }

            // Remove positions outside board
            if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT)
            {
                continue;
            }

            legal_moves.emplace_back(x, y);
        }
    }

    return legal_moves;
}
