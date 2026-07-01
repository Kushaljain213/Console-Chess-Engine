#ifndef MOVE_H
#define MOVE_H

#include "Position.h"
#include "Piece.h"

class Move
{
private:
    Position from;
    Position to;

    Piece* movedPiece;
    Piece* capturedPiece;

    bool movedPieceHadMoved;
    bool rookHadMoved;

public:
    Move();

    Move(const Position& from,
         const Position& to,
         Piece* movedPiece,
         Piece* capturedPiece = nullptr);

    Position getFrom() const;
    Position getTo() const;

    Piece* getMovedPiece() const;
    Piece* getCapturedPiece() const;

    bool getMovedPieceHadMoved() const;
    void setMovedPieceHadMoved(bool value);

    bool getRookHadMoved() const;
    void setRookHadMoved(bool value);


};

#endif