#include "piece.hpp"

Piece::Piece(PieceType piece_type, PieceColor piece_color)
    : piece_type_(piece_type)
    , piece_color_(piece_color)
{

}

// TODO const string& to string_view
Piece::Piece(PieceType piece_type, PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename)
    : piece_type_(piece_type)
    , piece_color_(piece_color)
{
    std::cout << "Loading texture (" << texture_filename <<  ") ...\n";

    IMG_Init(IMG_INIT_PNG);
    texture_ = IMG_LoadTexture(renderer, texture_filename.c_str());

    // Check if texture was loaded successfully
    if (texture_ == nullptr)
    {
        throw std::runtime_error("Failed to load piece texture");
    }

    std::cout << "Piece texture loaded successfully (" << texture_filename <<  ") ...\n";
}

Piece::~Piece()
{
    SDL_DestroyTexture(texture_);
}

PieceType Piece::GetPieceType() const
{
    return piece_type_;
}

PieceColor Piece::GetPieceColor() const
{
    return piece_color_;
}

const Position& Piece::GetPosition() const
{
    return position_;
}

void Piece::SetPosition(const Position &position)
{
    position_ = position;
}

SDL_Texture* Piece::GetTexture()
{
    return texture_;
}
