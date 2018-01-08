#include "board.hpp"
#include "test.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>

#define CHECKER_SIZE 75

void GUIprintBoard(board &,sf::RenderWindow &, sf::Sprite &, sf::Sprite &);

int main() {
  board game;
  uint64_t light, dark;

  sf::RenderWindow window(sf::VideoMode(600, 600), "Anubis - Checkers Playing AI", sf::Style::Close);
  window.setVerticalSyncEnabled(true);

  sf::Texture checkersBoard;
  if (!checkersBoard.loadFromFile("resources/checkersboard.png"))
  {
    printf("Error loading resource: Board.Exiting...\n");
    exit(1);
  }

  sf::Texture redCircle, blueCircle;

  if (!redCircle.loadFromFile("resources/red.png"))
  {
    printf("Error loading resource: Red piece.Exiting...\n");
    exit(1);
  }

  if (!blueCircle.loadFromFile("resources/blue.png"))
  {
    printf("Error loading resource: Blue piece.Exiting...\n");
    exit(1);
  }

  sf::Sprite boardDisplay;
  boardDisplay.setTexture(checkersBoard);

  sf::Sprite redChecker, blueChecker;
  redChecker.setTexture(redCircle);
  blueChecker.setTexture(blueCircle);

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      switch (event.type) {
        // window closed
        case sf::Event::Closed:
          window.close();
          break;

        default:
          break;
      }
    }

    // clear the window
    window.clear(sf::Color::Black);

    // draw the board
    window.draw(boardDisplay);
    GUIprintBoard(game, window, redChecker, blueChecker);
    // end the current frame
    // Get the values for dark and light

    // draw the pieces
    window.display();
  }
  return 0;
}

void GUIprintBoard(board &game, sf::RenderWindow &window, sf::Sprite &redChecker, sf::Sprite &blueChecker) {
  int multiple = CHECKER_SIZE;
  uint64_t light = game.getLight();
  uint64_t dark  = game.getDark();

  for(int row = 7; row >= 0; row--) {
    int row_start = row * 8;
    int row_end = row_start + 8;
    for(int col = row_start; col < row_end; col++) {

      int xPos = (col%8)*multiple;
      int yPos = (7-row)*multiple;

      if ( (1ULL << col) & light ) {
        redChecker.setPosition(xPos, yPos);
        window.draw(redChecker);
      }
      else if ( (1ULL << col) & dark ) {
        blueChecker.setPosition(xPos, yPos);
        window.draw(blueChecker);
      }
      else {;}
    }
   }
}


/*
int main() {
  board game;
  //manualTest(game);
  simpleMoveTest(game);


  //board game2;
  //game2.setPosition(DARK, Move(LIGHT_START, DARK_START, KING_START));
  //manualTest(game2);

  return 0;
}
*/
