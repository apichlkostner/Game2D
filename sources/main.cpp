#include <fstream>
#include <iostream>

#include "config.h"
#include "game.h"
#include "map.h"
#include "player.h"
#include "project_headers.h"
#include "tilemap.h"

int main() {
  // create window
  uint32_t window_width = mygame::mapconfig::MAP_SIZE.x * mygame::TILE_SIZE.x;
  uint32_t window_height = mygame::mapconfig::MAP_SIZE.y * mygame::TILE_SIZE.y;
  auto window = std::make_unique<sf::RenderWindow>(sf::VideoMode(window_width, window_height), "Game",
                                                   sf::Style::Titlebar | sf::Style::Close);
  window->setPosition(sf::Vector2i(500, 100));
  window->setVerticalSyncEnabled(true);
  window->setMouseCursorVisible(false);

  // set window icon
  sf::Image window_icon;
  window_icon.loadFromFile(mygame::WINDOW_ICON);
  window->setIcon(window_icon.getSize().x, window_icon.getSize().y, window_icon.getPixelsPtr());

  // create player
  auto player = std::make_unique<mygame::Player>();

  // create map
  auto map = std::make_unique<mygame::tilemap>();
  auto tiles_map = mygame::mapconfig::MAP;
  if (!map->load(mygame::TILESET_MAP, mygame::TILE_SIZE, std::move(tiles_map), mygame::mapconfig::MAP_SIZE)) {
    std::cout << "Couldn't load tileset " + mygame::TILESET_MAP << std::endl;
  }

  // create game class, inject window, player and map
  mygame::game g(std::move(window), std::move(player), std::move(map));

  // main loop
  sf::Clock clock;
  sf::Time timeSinceUpdate = sf::Time::Zero;
  while (g.isRunning()) {
    g.events();  // process events

    sf::Time deltaTime = clock.restart();
    timeSinceUpdate += deltaTime;
    while (timeSinceUpdate > mygame::TIME_UPDATE) {
      g.events();
      g.update(mygame::TIME_UPDATE);  // update state in fixed timesteps
      timeSinceUpdate -= mygame::TIME_UPDATE;
    }

    g.render();  // render game
  }

  return 0;
}