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
   std::cout << std::endl;
}

void board::makeMove(Move move) {
  light = move.valLight();
  dark  = move.valDark();
  king  = move.valKing();

  moveHistory.push_back(move);
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


void board::generateAllMoves(std::vector<Move> &moves) {
  uint64_t tempLight, tempDark, tempLightKing, tempDarkKing, tempKing,block;
  uint64_t lightKing, darkKing;
  block = light | dark;
  lightKing = light & king;
  darkKing  = dark & king;

  if (side == LIGHT) {
    for(int i=0; i<64; i++) {

      tempLight = light, tempDark = dark, tempKing = king;

      if( (1ULL << i) & light ) {
        uint64_t start = i;
        uint64_t end1 = start+7;
        uint64_t end2 = start+9;

        // If there is something over there already - we check beyond that to see captures...
        if ( (1ULL << end1) & block ) continue;
        if ( (1ULL << end2) & block ) continue;

        // If 7 is added to start, it causes "curling up"
        if (start % 8 != 0) {
          tempLight = tempLight & (~(1ULL << start)); //zero that square
          tempLight = tempLight | (1ULL << end1); //one at the new pos now
          Move move(tempLight, tempDark, tempKing);
          moves.push_back(move);
        }

        tempLight = light, tempDark = dark, tempKing = king;

        // If 9 is added to start, it causes "curling up"
        if (start % 8 != 7) {
          tempLight = tempLight & (~(1ULL << start)); //zero that square
          tempLight = tempLight | (1ULL << end2); //one at the new pos now
          Move move(tempLight, tempDark, tempKing);
          moves.push_back(move);
        }
      }
    }
  }

}
