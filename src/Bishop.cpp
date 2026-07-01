#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(const Position& position, Color color)
    : Piece(position, color, PieceType::BISHOP) {}

std::vector<Position> Bishop::getLegalMoves(const Board& board) const
{
    std::vector<Position> legalMoves;

    const int rowDirection[4] = {-1, -1, 1, 1};
    const int colDirection[4] = {-1, 1, -1, 1};

    for (int dir = 0; dir < 4; dir++)
    {
        int newRow = position.row;
        int newCol = position.col;

        while (true)
        {
            newRow += rowDirection[dir];
            newCol += colDirection[dir];

            Position newPosition(newRow, newCol);

            if (!newPosition.isValid())
                break;

            Piece* target = board.getPiece(newPosition);

            if (target == nullptr)
            {
                legalMoves.push_back(newPosition);
            }
            else
            {
                if (target->getColor() != color)
                    legalMoves.push_back(newPosition);

                break;
            }
        }
    }

    return legalMoves;
}