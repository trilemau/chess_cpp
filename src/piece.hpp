#pragma once

#include "libs.hpp"

#include "position.hpp"

class Piece
{
    PieceType piece_type_;
    PieceColor piece_color_;
    Position position_;

    bool texture_loaded_;
    SDL_Texture* texture_;

public:
    Piece(PieceType piece_type, PieceColor piece_color);
    Piece(PieceType piece_type, PieceColor piece_color, SDL_Renderer* renderer, const string& texture_filename);
    virtual ~Piece();

    bool operator==(const Piece& piece) const;
    bool operator!=(const Piece& piece) const;

    PieceType GetPieceType() const;
    PieceColor GetPieceColor() const;

    const Position& GetPosition() const;
    void SetPosition(const Position& position);

    SDL_Texture* GetTexture();

    virtual std::vector<Position> LegalMoves() const = 0;
};
