#include "King.h"
#include "Board.h"

King::King(const Position& position, Color color)
    : Piece(position, color, PieceType::KING) {}

std::vector<Position> King::getLegalMoves(const Board& board) const
{
    std::vector<Position> legalMoves;

    const int rowOffset[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int colOffset[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++)
    {
        Position newPosition(position.row + rowOffset[i],
                             position.col + colOffset[i]);

        if (!newPosition.isValid())
            continue;

        Piece* target = board.getPiece(newPosition);

        if (target == nullptr || target->getColor() != color)
        {
            legalMoves.push_back(newPosition);
        }
    }


    return legalMoves;
}