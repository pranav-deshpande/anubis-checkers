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
#include <vector>

/*
Don't work too much on one day.
*/

/*
Premature feature adding is also the root of all evil.
First complete the basic stuff.
*/

#define CHECKER_SIZE 75
#define INVALID -1

void GUIprintBoard(board &,sf::RenderWindow &, sf::Sprite &, sf::Sprite &);

int main() {
  board game;
  int initPos, targetPos;
  targetPos = initPos = INVALID;

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
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::MouseButtonPressed:
          if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
          {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);

            // now this makes us know which is the required checker selected!
            // coordinates in multiples of 75 obtained
            int x = localPosition.x - localPosition.x%CHECKER_SIZE;
            int y = localPosition.y - localPosition.y%CHECKER_SIZE;

            // map it to [0, 8)
            int actX = x/CHECKER_SIZE;
            int actY = y/CHECKER_SIZE;
            printf("actX: %d, actY: %d\n", actX, actY);

            // Obtain the position as per the bitboard representation
            int actPosition = (7-actY)*8 + (actX);

            uint64_t light = game.getLight();
            uint64_t dark  = game.getDark();
            uint64_t block = light | dark;

            if ( (1ULL << actPosition) & block ){
              initPos = actPosition;
            }
            else {
              initPos = INVALID;
            }
          }
          else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);

            // coordinates in multiples of 75 obtained
            int x = localPosition.x - localPosition.x%CHECKER_SIZE;
            int y = localPosition.y - localPosition.y%CHECKER_SIZE;

            // map it to [0, 8)
            int actX = x/CHECKER_SIZE;
            int actY = y/CHECKER_SIZE;

            // Obtain the position as per the bitboard representation
            int actPosition = (7-actY)*8 + (actX);

            uint64_t light = game.getLight();
            uint64_t dark  = game.getDark();
            uint64_t block = light | dark;

            if ( (1ULL << actPosition) & block ){
              targetPos = INVALID;
            }
            else {
              targetPos = actPosition;
            }
          }
          if ( initPos != INVALID && targetPos != INVALID ) {
            uint64_t light = game.getLight();
            uint64_t dark  = game.getDark();
            std::vector<Move> moveList;
            game.generateAllMoves(moveList);
            if ( (1ULL << initPos) & light ) {
              light = light & ~(1ULL << initPos);
              light = light | (1ULL << targetPos);
            }
            if ( (1ULL << initPos) & dark ) {
              dark = dark & ~(1ULL << initPos);
              dark = dark | (1ULL << targetPos);
            }
            bool valid = false;
            for(auto it = moveList.begin(); it != moveList.end(); it++) {
              if( it->valLight() == light && it->valDark() == dark ) {
                valid = true;
                game.makeMove(*it);
                game.printBoard();
                break;
              }
            }
            if(valid == false) {
              // do nothing
              ;
            }
          }


          break;

        default:
          break;
      }
    }

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
  int multiple = CHECKER_SIZE;
  uint64_t light = game.getLight();
  uint64_t dark  = game.getDark();

  for(int i = 0; i < 64; i++) {
    int xPos = (i%8) * multiple;
    int yPos = (7 - i/8) * multiple;
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
