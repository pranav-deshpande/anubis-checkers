#include "board.hpp"
#include "test.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

int main() {
  sf::RenderWindow window(sf::VideoMode(600, 600), "Anubis - Checkers Playing AI", sf::Style::Close);
  window.setVerticalSyncEnabled(true);

  sf::Texture checkersBoard;
  if (!checkersBoard.loadFromFile("checkersboard.png"))
  {
    printf("Error loading resource: Board.Exiting...\n");
    exit(1);
  }

  sf::Sprite boardDisplay;
  boardDisplay.setTexture(checkersBoard);

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

    // draw stuff now
    window.draw(boardDisplay);

    // end the current frame
    window.display();

  }
  return 0;
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
