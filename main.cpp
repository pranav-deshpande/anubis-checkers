#include "board.hpp"
#include "test.hpp"

int main() {
  board game;
  //manualTest(game);
  simpleMoveTest(game);

/*
  board game2;
  game2.setPosition(DARK, Move(LIGHT_START, DARK_START, KING_START));
  manualTest(game2);
*/
  return 0;
}
