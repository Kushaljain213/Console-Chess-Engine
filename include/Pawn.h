#ifndef PAWN_H
#define PAWN_H

#include <vector>
#include "Piece.h"

class Pawn: public Piece{
public:
    Pawn(const Position& position, Color color);
    std::vector<Position> getLegalMoves(const Board& board) const override;
};

#endif