#ifndef BOARD
#define BOARD

#include <cstdint>
#include <vector>

#define LIGHT 0
#define DARK 1

class board {
private:
  uint64_t light, dark, king;
  int side;
public:
  board();
  void printBoard();
  void generateAllMoves();
  void makeMove(uint64_t L, uint64_t D, uint64_t K);
  void undoMove();
};

#endif
