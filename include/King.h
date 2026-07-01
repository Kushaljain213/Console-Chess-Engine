#ifndef KING_H
#define KING_H

#include <vector>
#include "Piece.h"


class King: public Piece{
public:
    King(const Position& position, Color color);
    std :: vector<Position> getLegalMoves(const Board& board) const override;
};

#endif