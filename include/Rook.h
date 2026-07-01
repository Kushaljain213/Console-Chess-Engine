#ifndef ROOK_H
#define ROOK_H

#include <vector>
#include "Piece.h"


class Rook: public Piece{
public:
    Rook(const Position& position, Color color);
    std::vector<Position> getLegalMoves(const Board& board) const override;
};

#endif