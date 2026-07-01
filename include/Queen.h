#ifndef QUEEN_H
#define QUEEN_H

#include <vector>
#include "Piece.h"


class Queen: public Piece{
public:
    Queen(const Position& position, Color color);
    std::vector<Position> getLegalMoves(const Board& board) const override;
};

#endif