#include "MoveHistory.h"
#include "Board.h"

MoveHistory::MoveHistory() = default;

void MoveHistory::addMove(const Move& move){
    moves.push_back(move);
}

Move MoveHistory::getMove(size_t index) const{
    return moves.at(index);
}

size_t MoveHistory::size() const{
    return moves.size();
}
void MoveHistory::clear() {
    moves.clear();
}
bool MoveHistory::empty() const
{
    return moves.empty();
}

Move MoveHistory::getLastMove() const
{
    return moves.back();
}

Move MoveHistory::popMove()
{
    Move move = moves.back();
    moves.pop_back();
    return move;
}
