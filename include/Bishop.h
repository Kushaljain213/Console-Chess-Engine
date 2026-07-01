#ifndef BISHOP_H
#define BISHOP_H

#include <vector>
#include "Piece.h"

class Bishop: public Piece{
public:
    Bishop(const Position& position, Color color);
    std::vector<Position> getLegalMoves(const Board& board) const override;
};

#endif