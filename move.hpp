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

#ifndef MOVE
#define MOVE

#include <cstdint>

class Move {
private:
  uint64_t light, dark, king;
public:
  Move();
  Move(uint64_t L, uint64_t D, uint64_t K);
  uint64_t valLight();
  uint64_t valDark();
  uint64_t valKing();
  void print();
};

#endif
