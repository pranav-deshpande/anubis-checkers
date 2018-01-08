#ifndef BOARD
#define BOARD

// Remember - the numbers are going from right to left
// We are talking about board representation right now
/*
63 62 61 60 59 58 57 56
55 54 53 52 51 50 49 48
47 46 45 44 43 42 41 40
39 38 37 36 35 34 33 32
31 30 29 28 27 26 25 24
23 22 21 20 19 18 17 16
15 14 13 12 11 10 9  8
7  6  5  4  3  2  1  0
*/
// Example - 0x...........55 => 01010101 normally ...written in the above sense, we have:
// 10101010

/*
Premature optimization is the root of evil
*/

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
  void setPosition(uint64_t side, Move position);
  void printBoard();
  void generateAllMoves(std::vector<Move> &);
  void makeMove(Move);
  void undoMove();
  uint64_t getLight();
  uint64_t getDark();
  // yeah...we could do a getKing here as well, right now..I am working on graphics..so no..
};

#endif
