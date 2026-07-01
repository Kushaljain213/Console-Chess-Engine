#include "Knight.h"
#include "Board.h"
Knight::Knight(const Position& position, Color color): Piece(position,color,PieceType::KNIGHT){}

std::vector<Position> Knight::getLegalMoves(const Board& board) const{
    std::vector<Position> legalMoves;
    const int rowOffsets[8] = {-2,-2,-1,-1,1,1,2,2};
    const int colOffsets[8] = {-1,1,-2,2,-2,2,-1,1};

    for (int i = 0; i < 8; i++) {
       int newRow = position.row + rowOffsets[i];
       int newCol = position.col + colOffsets[i];
       Position newPosition(newRow, newCol);
       if (!newPosition.isValid()) continue;
       Piece* target = board.getPiece(newPosition);
       if (target == nullptr || target->getColor() != color) {
           legalMoves.push_back(newPosition);
       }
    }

    return legalMoves;
}