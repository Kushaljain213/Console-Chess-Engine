#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>
#include "Piece.h"

class Knight: public Piece{
public:
    Knight(const Position& position, Color color);
    std::vector<Position> getLegalMoves(const Board& board) const override;
};

#endif