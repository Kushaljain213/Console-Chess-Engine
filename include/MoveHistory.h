#ifndef MOVEHISTORY_H
#define MOVEHISTORY_H

#include <vector>
#include "Move.h"

class MoveHistory{
private:
    std::vector<Move> moves;

public:
    MoveHistory();

    void addMove(const Move& move);

    Move getMove(size_t index) const;

    Move getLastMove() const;

    Move popMove();

    bool empty() const;

    size_t size() const;

    void clear();
};

#endif