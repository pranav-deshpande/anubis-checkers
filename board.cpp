#include "board.hpp"
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdint>

#define LIGHT 0
#define DARK 1

board::board() {
  side  = LIGHT;
  light = 0x000000000055aa55;
  dark  = 0xaa55aa0000000000;
  king  = 0x0000000000000000;
}

void board::printBoard() {
  for(int i = 7; i >= 0; i--) {
    int j = i * 8;
    for(int k = j; k < j + 8; k++) {
      if ( (1ULL << k) & light ) {
        std::cout << 'l';
      }
      else if ( (1ULL << k) & dark ) {
        std::cout << 'd';
      }
      else
        std::cout << '0';
    }
    std::cout << std::endl;
   }
   std::cout << "Debug data: " << std::endl;
   printf("light: %lx\ndark: %lx\nking: %lx\n", light, dark, king);
}

void board::makeMove(uint64_t L, uint64_t D, uint64_t K) {
  light = L;
  dark  = D;
  king  = K;
}

void board::undoMove() {
}