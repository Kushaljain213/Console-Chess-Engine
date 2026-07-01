#include "MoveValidator.h"
#include <cmath>

bool MoveValidator::isMoveLegal(Board& board,
                                const Move& move,
                                Color currentPlayer) const
{
    Piece* movedPiece = move.getMovedPiece();

    // Special checks for castling
    if (movedPiece->getType() == PieceType::KING)
    {
        int diff = move.getTo().col - move.getFrom().col;

        if (std::abs(diff) == 2)
        {
            // Determine rook position
            int rookCol = (diff > 0) ? 7 : 0;

            Piece* rook = board.getPiece(Position(move.getFrom().row, rookCol));

            if (rook == nullptr)
                return false;

            if (rook->getType() != PieceType::ROOK)
                return false;

            if (rook->getColor() != currentPlayer)
                return false;

            if (rook->getHasMoved())
                return false;

            // Check squares between king and rook
            int start = std::min(move.getFrom().col, rookCol) + 1;
            int end = std::max(move.getFrom().col, rookCol);

            for (int col = start; col < end; col++)
            {
                if (board.getPiece(Position(move.getFrom().row, col)) != nullptr)
                    return false;
            }

            Color enemy =
                (currentPlayer == Color::WHITE)
                    ? Color::BLACK
                    : Color::WHITE;

            // King cannot already be in check
            if (CheckDetector::isKingInCheck(board, currentPlayer))
                return false;

            // Square the king passes through
            Position middle(
                move.getFrom().row,
                move.getFrom().col + (diff > 0 ? 1 : -1));

            if (isSquareUnderAttack(board, middle, enemy))
                return false;

            // Final square
            if (isSquareUnderAttack(board, move.getTo(), enemy))
                return false;
        }
    }

    // Check whether move leaves own king in check
    board.makeMove(move);

    bool kingInCheck =
        CheckDetector::isKingInCheck(board, currentPlayer);

    board.undoMove(move);

    return !kingInCheck;
}

bool MoveValidator::isSquareUnderAttack(
    const Board& board,
    const Position& square,
    Color attackerColor)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Piece* piece = board.getPiece(Position(row, col));

            if (piece == nullptr)
                continue;

            if (piece->getColor() != attackerColor)
                continue;

            std::vector<Position> moves = piece->getLegalMoves(board);

            for (const Position& move : moves)
            {
                if (move == square)
                    return true;
            }
        }
    }

    return false;
}

std::vector<Position> MoveValidator::getLegalMoves(Board& board,
                                                   Piece* piece,
                                                   Color currentPlayer) const
{
    std::vector<Position> legalMoves;

    // Normal piece moves
    std::vector<Position> candidateMoves = piece->getLegalMoves(board);

    // Add castling attempts for king
    if (piece->getType() == PieceType::KING &&
        !piece->getHasMoved())
    {
        Position pos = piece->getPosition();

        candidateMoves.push_back(Position(pos.row, 6)); // Kingside
        candidateMoves.push_back(Position(pos.row, 2)); // Queenside
    }

    // Keep only legal moves
    for (const Position& to : candidateMoves)
    {
        Move move(
            piece->getPosition(),
            to,
            piece,
            board.getPiece(to));

        if (isMoveLegal(board, move, currentPlayer))
        {
            legalMoves.push_back(to);
        }
    }

    return legalMoves;
}

bool MoveValidator::hasLegalMove(Board& board, Color player) const
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Piece* piece = board.getPiece(Position(row, col));

            if (piece == nullptr)
                continue;

            if (piece->getColor() != player)
                continue;

            std::vector<Position> moves =
                getLegalMoves(board, piece, player);

            if (!moves.empty())
                return true;
        }
    }

    return false;
}