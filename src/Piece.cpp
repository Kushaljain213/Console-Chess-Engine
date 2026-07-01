#include "Piece.h"
#include "Board.h"

Piece::Piece(Position position, Color color, PieceType type)
    : position(position),
      color(color),
      type(type),
      hasMoved(false)
{
}
bool Piece::getHasMoved() const
{
    return hasMoved;
}

void Piece::setHasMoved(bool moved)
{
    hasMoved = moved;
}

Position Piece::getPosition() const{
    return position;
}
Color Piece::getColor() const{
    return color;
}
PieceType Piece::getType() const{
    return type;
}

void Piece::setPosition(const Position& position) {
    this->position = position;
}

