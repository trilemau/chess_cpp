#include "piece.hpp"

Piece::Piece(PieceType piece_type, PieceColor piece_color)
    : piece_type_(piece_type)
    , piece_color_(piece_color)
    , position_(0, 0) // TODO not correct
    , texture_loaded_(false)
    , texture_(nullptr)
{

}

// TODO const string& to string_view
Piece::Piece(PieceType piece_type, PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename)
    : piece_type_(piece_type)
    , piece_color_(piece_color)
    , position_(0, 0) // TODO not correct
    , texture_loaded_(false)
{
    IMG_Init(IMG_INIT_PNG);
    texture_ = IMG_LoadTexture(renderer, texture_filename.c_str());

    // Check if texture was loaded successfully
    if (texture_ == nullptr)
    {
        throw std::runtime_error("Failed to load piece texture=" + texture_filename);
    }

    texture_loaded_ = true;
}

Piece::~Piece()
{
    if (texture_loaded_)
    {
        SDL_DestroyTexture(texture_);
    }
}

bool Piece::operator==(const Piece& piece) const
{
    return piece_type_ == piece.GetPieceType()
        && piece_color_ == piece.GetPieceColor()
        && position_ == piece.GetPosition();
};

bool Piece::operator!=(const Piece& piece) const
{
    return !(*this == piece);
};

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
