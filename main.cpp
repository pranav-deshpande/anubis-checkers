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

#include "board.hpp"
#include "move.hpp"
#include "test.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cassert>

/*
Don't work too much on one day.
*/

/*
Premature feature adding is also the root of all evil.
First complete the basic stuff.
*/

#define CHECKER_SIZE 75

void GUIprintBoard(board &,sf::RenderWindow &, sf::Sprite &, sf::Sprite &);

int main() {
  board game;

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

        case sf::Event::MouseButtonPressed:
          if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //printf("The left mouse button was pressed.\n");
            ;
          }
          if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
          {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);

            // now this makes us know which is the required checker selected!
            // coordinates in multiples of 75 obtained
            int x = localPosition.x - localPosition.x%CHECKER_SIZE;
            int y = localPosition.y - localPosition.y%CHECKER_SIZE;
            //printf("X: %d, Y: %d\n", x, y);

            // map it to [0, 8)
            int actX = x/75;
            int actY = y/75;
            printf("actX: %d, actY: %d\n", actX, actY);

            // Obtain the position as per the bitboard representation
            int actPosition = (7-actY)*8 + (7-actX);
            printf("actPosition: %d\n", actPosition);

            // Test the formula devised
            int xPos = (7 - actPosition%8);
            int yPos = (7 - actPosition/8);
            printf("xPos: %d, yPos: %d\n", xPos, yPos);

            // As a temporary act, I will make some piece disappear
            uint64_t light = game.getLight();
            uint64_t dark  = game.getDark();
            uint64_t king  = game.getKing();

            if ( ((1ULL << actPosition) & light) ) {
              light = light & (~(1ULL << actPosition));
              printf("I was here\n");
            }

            if ( ((1ULL << actPosition) & dark) ) {
              dark = dark & (~(1ULL << actPosition));
              //printf("I was here as well\n");
            }

            Move move(light, dark, king);
            game.makeMove(move);
            //move.print();
            //putchar('\n');
            game.printBoard();
            putchar('\n');

            // actual moves will involve checking stuff
            /*
            vector<Move> moveList;
            generateAllMoves(moveList);
            */
          }
          break;

        default:
          break;
      }
    }

    // now get the mouse input...uh ok got to do this yeah...
    // tried placing this inside the sf::Event::Mouse thing, it was SLOW

    // clear the window
    window.clear(sf::Color::Black);

    // draw the board
    window.draw(boardDisplay);

    // draw the pieces
    GUIprintBoard(game, window, redChecker, blueChecker);

    // end the current frame
    window.display();
  }
  return 0;
}

void GUIprintBoard(board &game, sf::RenderWindow &window, sf::Sprite &redChecker, sf::Sprite &blueChecker) {

  // currently, this is printing a laterally flipped board. Hence, it is wrong
  // This function is to be corrected

  int multiple = CHECKER_SIZE;
  uint64_t light = game.getLight();
  uint64_t dark  = game.getDark();

  for(int i = 0; i < 64; i++) {
    int xPos = (7 - i%8) * multiple;
    int yPos = (7 - i/8) * multiple;

    //printf("X: %d, Y: %d\n", xPos, yPos);

    if ( (1ULL << i) & light ) {
      redChecker.setPosition(xPos, yPos);
      window.draw(redChecker);
    }
    else if ( (1ULL << i) & dark ) {
      blueChecker.setPosition(xPos, yPos);
      window.draw(blueChecker);
    }
    else {;}
  }
}

/*
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

      // integrity check for my formula above
      assert(((7-yPos)*8 + (7-xPos)) == col);

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
*/

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
