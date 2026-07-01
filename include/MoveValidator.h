#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H

#include "Board.h"
#include "Move.h"
#include "CheckDetector.h"
#include <vector>

class MoveValidator
{
public:
    bool isMoveLegal(Board& board,
                     const Move& move,
                     Color currentPlayer) const;

    bool hasLegalMove(Board& board,
                      Color player) const;

    std::vector<Position> getLegalMoves(
        Board& board,
        Piece* piece,
        Color currentPlayer) const;

    static bool isSquareUnderAttack(
        const Board& board,
        const Position& square,
        Color attackerColor);
};

#endif