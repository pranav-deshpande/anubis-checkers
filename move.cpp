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
}
