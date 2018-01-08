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

#include "move.hpp"
#include <cstdio>

#define __STDC_FORMAT_MACROS
#include <cinttypes>

Move::Move() {
  light = dark = king = 0x0000000000000000;
}

Move::Move(uint64_t L, uint64_t D, uint64_t K){
  light = L;
  dark  = D;
  king  = K;
}

uint64_t Move::valLight() {
  return light;
}

uint64_t Move::valDark() {
  return dark;
}

uint64_t Move::valKing() {
  return king;
}

void Move::print() {
  printf("Light: 0x%" PRIx64 "\nDark: 0x%" PRIx64 "\nKing: 0x%" PRIx64, light, dark, king);
  putchar('\n');
}
