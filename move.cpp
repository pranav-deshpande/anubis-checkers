#include "board.hpp"
#include <iostream>

// I will totally avoid the move generation for kings now
// Let us worry about wrap arounds and out of boards later
// First I will write code only for the light side
// Then for the dark side

void board::generateAllMoves() {
  uint64_t tempLight, tempDark, tempKing, block;
  tempKing = king;
  // Note that this is just a temporary vector for testing purposes
  std::vector <uint64_t> moveList;
  block = light | dark;
  
  if (side == LIGHT) {
    for(int i = 0; i < 64; i++) {
      if((1ULL << i) & light) {

      	// Normal moves

        if(~(( 1ULL << (i+7) ) & block)) {
	        tempLight = light;
	        
	        // Remove the bit - 7
	        tempLight = tempLight & ~( 1ULL << i);
	        // Set the bit - 7
	        tempLight = tempLight | ( 1ULL << (i+7) );
	        // update moveList
	        moveList.push_back(tempLight);
	    }   
	    if(~(( 1ULL << (i+9) ) & block)) {   
	        tempLight = light;
	        
	        // Remove the bit - 9
	        tempLight = tempLight & ~(1ULL << i);
	        // Set the bit - 9
	        tempLight = tempLight | ( 1ULL << (i+9) );
	        // update moveList
	        moveList.push_back(tempLight);
	    }

	    // Captures

        if(~(( 1ULL << (i+7) ) & block)) {
        	if(( 1ULL << (i+14) ) & dark) {
	        	tempLight = light;
		        tempDark = dark;
		        // Remove the bit from light
		        tempLight = tempLight & ~( 1ULL << i);
		        // Remove the bit 7 from dark
		        tempDark = tempDark & ~( 1ULL << (i+7) );
		        // Add light bit to position 14
		        tempLight = tempLight | (1ULL << (i+14));
		        // update moveList
		        moveList.push_back(tempLight);
		    }
	    }   
	    
	    if(~(( 1ULL << (i+9) ) & block)) {
        	if(( 1ULL << (i+18) ) & dark) {
	        	tempLight = light;
		        tempDark = dark;
		        // Remove the bit from light
		        tempLight = tempLight & ~( 1ULL << i);
		        // Remove the bit 7 from dark
		        tempDark = tempDark & ~( 1ULL << (i+9) );
		        // Add light bit to position 14
		        tempLight = tempLight | (1ULL << (i+18));
		        // update moveList
		        moveList.push_back(tempLight);
		    }
	    }   
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
    
