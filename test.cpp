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

#include "test.hpp"
#include "board.hpp"
#include <cstdio>
#include <cstdlib>
#include <fstream>

/*
// Taken from https://stackoverflow.com/questions/7349689/how-to-print-using-cout-the-way-a-number-is-stored-in-memory
template<typename T>
void printBin(const T& t){
    size_t nBytes=sizeof(T);
    char* rawPtr((char*)(&t));
    for(size_t byte=0; byte<nBytes; byte++){
        for(size_t bit=0; bit<8; bit++){
            std::cout<<(((rawPtr[byte])>>bit)&1);
        }
    }
    std::cout<<std::endl;
};
// -- code taken from stackoverflow ends here
*/

void manualTest(board &game) {
  game.printBoard();
  std::vector<Move> moves;
  game.generateAllMoves(moves);

  if(moves.empty()) {
    printf("No valid moves\n");
    exit(0);
  }
  printf("The total number of moves valid now is: %d\n", moves.size());

  for(auto it = moves.begin(); it != moves.end(); it++) {
    //it->print();
    getchar();
    game.makeMove(*it);
    game.printBoard();

    getchar();
    game.undoMove();
    game.printBoard();
  }

  /*
  for(int i = 0; i < 64; i++) {
    printBin((1ULL << i));
  }
  */
}

void simpleMoveTest(board &game) {
  int gameSize = 0;

  std::vector<Move> movesA;
  std::vector<Move> movesB;
  game.generateAllMoves(movesA);

  for(int i = 0; i < movesA.size(); i++) {
      game.makeMove(movesA[i]);
      game.printBoard();
      game.generateAllMoves(movesB);
      for(int i = 0; i < movesB.size(); i++) {
        gameSize += 1;
        game.makeMove(movesB[i]);
        game.printBoard();
        game.undoMove();
        game.printBoard();
      }
      game.undoMove();
      game.printBoard();
  }

  printf("Game Size: %d\n", gameSize);
}
