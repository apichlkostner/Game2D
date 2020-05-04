#include <iostream>

#include "game.h"
#include "player.h"
#include "project_headers.h"

int main() {
  auto window =
      std::make_unique<sf::RenderWindow>(sf::VideoMode(1024, 1024), "Game", sf::Style::Titlebar | sf::Style::Close);
  window->setPosition(sf::Vector2i(500, 300));
  window->setVerticalSyncEnabled(true);
  window->setMouseCursorVisible(false);

  auto player = std::make_unique<mygame::Player>();
  player->setRadius(10);
  player->setOutlineColor(sf::Color::Red);
  player->setOutlineThickness(1.f);

  mygame::game g(std::move(window), std::move(player));

  sf::Clock clock;
  while (g.isRunning()) {
    sf::Time deltaTime = clock.restart();
    g.events();
    g.update(deltaTime);
    g.render();
  }

  return 0;
}