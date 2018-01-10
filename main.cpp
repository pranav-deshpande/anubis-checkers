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
#include <cinttypes>

/*
Don't work too much on one day.
*/

/*
Premature feature adding is also the root of all evil.
First complete the basic stuff.
*/

#define CHECKER_SIZE 75
#define INVALID -1
#define __STDC_FORMAT_MACROS

void GUIprintBoard(board &,sf::RenderWindow &, sf::Sprite &, sf::Sprite &);
void playMoveIfValid(board &, int, int);

int main() {
  board game;
  int initPos, targetPos;
  //manualTest(game);

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

  initPos   = INVALID;
  targetPos = INVALID;
  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        default:
          break;
      }
    }
    if ( initPos != INVALID && targetPos != INVALID ) {
      playMoveIfValid(game, initPos, targetPos);
      initPos   = INVALID;
      targetPos = INVALID;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && targetPos == INVALID)
    {
      sf::Vector2i localPosition = sf::Mouse::getPosition(window);
      int x = (localPosition.x - localPosition.x%CHECKER_SIZE)/CHECKER_SIZE;
      int y = (localPosition.y - localPosition.y%CHECKER_SIZE)/CHECKER_SIZE;
      initPos = (7-y)*8 + (7-x);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && initPos != INVALID) {
      sf::Vector2i localPosition = sf::Mouse::getPosition(window);
      int x = (localPosition.x - localPosition.x%CHECKER_SIZE)/CHECKER_SIZE;
      int y = (localPosition.y - localPosition.y%CHECKER_SIZE)/CHECKER_SIZE;
      targetPos = (7-y)*8 + (7-x);
    }
    window.clear(sf::Color::Black);
    window.draw(boardDisplay);
    GUIprintBoard(game, window, redChecker, blueChecker);
    window.display();
  }
  return 0;
}

void GUIprintBoard(board &game, sf::RenderWindow &window, sf::Sprite &redChecker, sf::Sprite &blueChecker) {
  int multiple = CHECKER_SIZE;
  uint64_t light = game.getLight();
  uint64_t dark  = game.getDark();

  for(int i = 63; i >= 0; i--) {
    int xPos = (7 - i%8) * multiple;
    int yPos = (7 - i/8) * multiple;
    if ( (1ULL << i) & light ) {
      redChecker.setPosition(xPos, yPos);
      window.draw(redChecker);
    }
    if ( (1ULL << i) & dark ) {
      blueChecker.setPosition(xPos, yPos);
      window.draw(blueChecker);
    }
    else {;}
  }
}

void playMoveIfValid(board &game, int initPos, int targetPos) {
  int side = game.getSide();
  uint64_t newLight = game.getLight();
  uint64_t newDark  = game.getDark();

  newLight = newLight & ~ (1ULL<<initPos);
  newLight = newLight | (1ULL<<targetPos);

  newDark = newDark & ~ (1ULL<<initPos);
  newDark = newDark | (1ULL<<targetPos);

  std::vector<Move> moves;
  game.generateAllMoves(moves);

  for(int i = 0; i < moves.size(); i++) {
    if(side == LIGHT) {
      if(newLight == moves[i].valLight()) {
        game.makeMove(moves[i]);
        //printf("Light: 0x%" PRIx64 "\nDark: 0x%" PRIx64 "\n", game.getLight(), game.getDark());
        break;
      }
    }
    if(side == DARK) {
      if(newDark == moves[i].valDark()) {
        game.makeMove(moves[i]);
        //printf("Light: 0x%" PRIx64 "\nDark: 0x%" PRIx64 "\n", game.getLight(), game.getDark());
        break;
      }
    }
  }

}
