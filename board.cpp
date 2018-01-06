// Remember - the numbers are going from right to left
// We are talking about board representation right now
/*
63 62 61 60 59 58 57 56
...
...
15 14 13 12 11 10 9  8
7  6  5  4  3  2  1  0
*/
// Example - 0x...........55 => 01010101 normally ...written in the above sense, we have:
// 10101010
#include "board.hpp"
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdint>

board::board() {
  side  = LIGHT;

  light = LIGHT_START;
  dark  = DARK_START;
  king  = KING_START;

  moveHistory.clear();
}

void board::printBoard() {
  for(int row = 7; row >= 0; row--) {
    int row_start = row * 8;
    int row_end = row_start + 8;
    for(int col = row_start; col < row_end; col++) {
      if ( (1ULL << col) & light ) {
        std::cout << 'l';
      }
      else if ( (1ULL << col) & dark ) {
        std::cout << 'd';
      }
      else
        std::cout << '0';
    }
    std::cout << std::endl;
   }
}

void board::makeMove(Move move) {
  light = move.valLight();
  dark  = move.valDark();
  king  = move.valKing();
}

void board::undoMove() {
  if(moveHistory.empty()) {
    printf("Error, no moves to undo!!\n");
    exit(0);
  }

  int index = moveHistory.size() - 1;
  light = moveHistory[index].valLight();
  dark  = moveHistory[index].valDark();
  king  = moveHistory[index].valKing();

  moveHistory.pop_back();
}
