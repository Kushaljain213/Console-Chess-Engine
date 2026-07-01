#include "Queen.h"
#include "Board.h"

Queen::Queen(const Position& position, Color color)
    : Piece(position, color, PieceType::QUEEN) {}

std::vector<Position> Queen::getLegalMoves(const Board& board) const
{
    std::vector<Position> legalMoves;

    const int rowDirection[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    const int colDirection[8] = {0, 0, -1, 1, -1, 1, -1, 1};

    for (int dir = 0; dir < 8; dir++)
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