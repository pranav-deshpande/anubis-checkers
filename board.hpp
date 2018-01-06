#ifndef BOARD
#define BOARD

#include <cstdint>
#include <vector>
#include "move.hpp"

#define LIGHT 0
#define DARK  1
#define LIGHT_START 0x000000000055aa55
#define DARK_START  0xaa55aa0000000000
#define KING_START  0x0000000000000000

class board {
private:
  uint64_t light, dark, king;
  int side;
  std::vector <Move> moveHistory;
public:
  board();
  void printBoard();
  void generateAllMoves(std::vector<Move> &);
  void makeMove(Move);
  void undoMove();
};

#endif
