#include "Position.h"

Position::Position(){
    row = 0;
    col = 0;
}

Position::Position(int row, int col){
    this->row = row;
    this->col = col;
}

bool Position::isValid() const{
    return row >= 0 && row < 8 &&
           col >= 0 && col < 8;
}

bool Position::operator==(const Position &other) const{
    return row == other.row &&
           col == other.col;
}

bool Position::operator!=(const Position &other) const{
    return !(*this == other);
}

Position Position::fromChessNotation(const std::string &notation){
    int col = notation[0] - 'a';
    int row = 8 - (notation[1] - '0');

    return Position(row, col);
}

std::string Position::toChessNotation() const{
    std::string s;

    s += char('a' + col);
    s += char('8' - row);

    return s;
}