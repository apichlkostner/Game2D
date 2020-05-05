#include <iostream>

#include "config.h"
#include "game.h"
#include "player.h"
#include "project_headers.h"

int main() {
  auto window =
      std::make_unique<sf::RenderWindow>(sf::VideoMode(1024, 832), "Game", sf::Style::Titlebar | sf::Style::Close);
  window->setPosition(sf::Vector2i(500, 100));
  window->setVerticalSyncEnabled(true);
  window->setMouseCursorVisible(false);

  auto player = std::make_unique<mygame::Player>();

  mygame::game g(std::move(window), std::move(player));

  sf::Clock clock;
  sf::Time timeSinceUpdate = sf::Time::Zero;
  while (g.isRunning()) {
    g.events();

    sf::Time deltaTime = clock.restart();
    timeSinceUpdate += deltaTime;
    while (timeSinceUpdate > mygame::TIME_UPDATE) {
      g.events();
      g.update(mygame::TIME_UPDATE);
      timeSinceUpdate -= mygame::TIME_UPDATE;
    }

    g.render();
  }

  return 0;
}