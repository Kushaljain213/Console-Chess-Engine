#ifndef CHECKDETECTOR_H
#define CHECKDETECTOR_H

#include "Board.h"
#include "Position.h"
#include "Piece.h"

class CheckDetector
{
public:
    static Position findKing(const Board& board, Color kingColor);

    static bool isSquareAttacked(const Board& board,
                                 const Position& square,
                                 Color attackingColor);

    static bool isKingInCheck(const Board& board,
                       Color kingColor);
};

#endif