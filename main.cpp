#include "board.hpp"
#include "test.hpp"
#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Anubis - Checkers Playing AI");

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
