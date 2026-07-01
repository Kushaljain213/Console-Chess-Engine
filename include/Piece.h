#ifndef PIECE_H
#define PIECE_H

#include<vector>
#include "Position.h"


class Board;
enum class Color{
    WHITE,
    BLACK
};

enum class PieceType{
    PAWN,
    KNIGHT,
    KING,
    QUEEN,
    BISHOP,
    ROOK
};

class Piece{
protected:
    Position position;
    Color color;
    PieceType type;
    bool hasMoved;
public:
    Piece(Position position, Color color, PieceType type);
    virtual ~Piece() = default;
    Position getPosition() const;
    Color getColor() const;
    PieceType getType() const;
    bool getHasMoved() const;
    void setHasMoved(bool moved);
    void setPosition(const Position& position);

    virtual std::vector<Position> getLegalMoves(const Board& board) const = 0;
};

#endif

