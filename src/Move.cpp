#include "Move.h"

Move::Move()
    : movedPiece(nullptr),
      capturedPiece(nullptr),
      movedPieceHadMoved(false),
      rookHadMoved(false)

{
}


Move::Move(const Position& from,
           const Position& to,
           Piece* movedPiece,
           Piece* capturedPiece)
    : from(from),
      to(to),
      movedPiece(movedPiece),
      capturedPiece(capturedPiece),
      movedPieceHadMoved(false),
      rookHadMoved(false)

{
}

Position Move::getFrom() const {
    return from;
}

Position Move::getTo() const {
    return to;
}

Piece* Move::getMovedPiece() const {
    return movedPiece;
}

Piece* Move::getCapturedPiece() const {
    return capturedPiece;
}
bool Move::getMovedPieceHadMoved() const
{
    return movedPieceHadMoved;
}

void Move::setMovedPieceHadMoved(bool value)
{
    movedPieceHadMoved = value;
}
bool Move::getRookHadMoved() const
{
    return rookHadMoved;
}

void Move::setRookHadMoved(bool value)
{
    rookHadMoved = value;
}
