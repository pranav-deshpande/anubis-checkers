#ifndef BOARD
#define BOARD

#include <cstdint>

class board {
private:
  uint64_t white, black, king;
public:
  board();
  void printBoard();
  void generateAllMoves();
  void makeMove();
  void undoMove();
};

#endif
