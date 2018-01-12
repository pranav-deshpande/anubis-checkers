/*
Anubis - Checkers Game
Copyright (C) 2017-2018 Pranav Deshpande

This file is a part of Anubis.

Anubis is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

Anubis is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Anubis. If not, see <http://www.gnu.org/licenses/>.
*/

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

// However

#include "board.hpp"
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdint>

#define LIGHT_TEST 0x108a55aa
#define DARK_TEST 0x55aa510800000000

board::board() {
  setPosition(LIGHT, Move(LIGHT_START, DARK_START, KING_START));
}

void board::setPosition(uint64_t side, Move position) {
  moveHistory.clear();
  this->side = side;

  light = position.valLight();
  dark  = position.valDark();
  king  = position.valKing();

  // This position is stored in the move history due to undoMove() issues
  moveHistory.push_back(Move(light, dark, king));
}

int board::getSide() {
  return side;
}

uint64_t board::getLight() {
  return light;
}

uint64_t board::getDark() {
  return dark;
}

uint64_t board::getKing() {
  return king;
}

uint64_t board::getBlock() {
  return (light | dark);
}

void board::printBoard() {
  for(int row = 7; row >= 0; row--) {
    int row_start = row * 8;
    int row_end = row_start + 8;
    for(int pos = row_end - 1; pos >= row_start; pos--) {
      if ( (1ULL << pos) & light ) {
        std::cout << 'l';
      }
      else if ( (1ULL << pos) & dark ) {
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

  // switch sides
  side = !side;

  moveHistory.push_back(move);
}

void board::undoMove() {
  if(moveHistory.empty() || moveHistory.size() == 1) {
    printf("Error, no moves to undo!!\n");
    exit(0);
  }

  int index = moveHistory.size() - 1;
  light = moveHistory[index-1].valLight();
  dark  = moveHistory[index-1].valDark();
  king  = moveHistory[index-1].valKing();

  // switch sides
  side = !side;

  moveHistory.pop_back();
}
