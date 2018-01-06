#include "board.hpp"
#include "move.hpp"
#include <iostream>

// All multiples of 8 are corner squares - avoid addding 7 to these
// All multiples of 8 minus 1 are corner squares - avoid adding 9 these

void board::generateAllMoves() {
  uint64_t tempLight, tempDark, tempKing, block;
  block = light | dark;
  tempLight = light;
  tempDark  = dark;
  tempKing  = king;

  int count = 0;

  for(int i=0; i<64; i++) {
    if( (1ULL << i) & light ) {
      count++;
    }
  }

  std::cout << count << std::endl;

}
