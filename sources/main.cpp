#include <iostream>

#include "game.h"
#include "project_headers.h"

int main() {
  auto window =
      std::make_unique<sf::RenderWindow>(sf::VideoMode(640, 480), "Game", sf::Style::Titlebar | sf::Style::Close);
  window->setPosition(sf::Vector2i(500, 300));
  window->setVerticalSyncEnabled(true);

  mygame::game g(std::move(window));

  while (g.isRunning()) {
    g.events();
    g.render();
  }

  return 0;
}