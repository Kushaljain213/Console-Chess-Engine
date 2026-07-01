#ifndef POSITION_H
#define POSITION_H

#include <string>

class Position{
public:
    int row, col;
    static Position fromChessNotation(const std::string& notation);
    std::string toChessNotation() const;
    Position();
    Position(int row, int col);
    bool isValid() const;
    bool operator == (const Position& other) const;
    bool operator != (const Position& other) const;
};

#endif