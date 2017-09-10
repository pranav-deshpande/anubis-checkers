#include "board.hpp"
#include <iostream>

// I will totally avoid the move generation for kings now
// Let us worry about wrap arounds and out of boards later

void board::generateAllMoves() {
  uint64_t temp, tempKing;
  tempKing = king;
  std::vector <uint64_t> moveList;
  if (side == LIGHT) {
    for(int i = 0; i < 64; i++) {
      if((1ULL << i) & light) {
        
        temp = light;
        
        // Remove the bit - 7
        temp = temp & ~( 1ULL << i);
        // Set the bit - 7
        temp = temp | ( 1ULL << (i+7) );
        // update moveList
        moveList.push_back(temp);
        
        temp = light;
        
        // Remove the bit - 9
        temp = temp & ~(1ULL << i);
        // Set the bit - 9
        temp = temp | ( 1ULL << (i+9) );
        // update moveList
        moveList.push_back(temp);
      }
    }
  }
  uint64_t ol = light, od = dark, ok = king;
  std::cout << "The size of the moveList is: " << moveList.size() << std::endl;
  for(auto it = moveList.begin(); it != moveList.end(); it++) {
    std::cout << std::endl;
    light = ol;
    dark = od;
    king = ok;
    uint64_t move = *it;
    makeMove(move, dark, king);
    printBoard();
    std::cout << std::endl;
  }
}
    