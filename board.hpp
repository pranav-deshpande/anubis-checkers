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
#define LIGHT_START 0x0000000000aa55aa
#define DARK_START  0x55aa550000000000
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
  int getSide();
  uint64_t getLight();
  uint64_t getDark();
  uint64_t getKing();
};

#endif
