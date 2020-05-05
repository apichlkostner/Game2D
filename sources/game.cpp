#include "game.h"

#include <assert.h>

#include <cmath>
#include <iostream>

#include "project_headers.h"
#include "tilemap.h"

namespace mygame {

game::game(std::unique_ptr<sf::RenderWindow> window, std::unique_ptr<Player> player)
    : window_(std::move(window)),
      map_(std::make_unique<tilemap>()),
      player_(std::move(player)),
      player_position{20, 20},
      player_size_(1.),
      player_size_factor_(0.1),
      running(true) {
  assert(window_);
  assert(player_);
  assert(map_);

  const std::vector<uint8_t> level {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 2, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 2, 3, 3, 0, 0, 0, 0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 2, 3, 0, 0,
      0, 0, 0, 0, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 4, 4,
      1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 4, 4, 4, 1, 1, 1, 1, 1,
      1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0, 0,
      0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0,
      0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
      2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0,
      0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
      2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2,
      2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  };

  if (!map_->load(TILESET_MAP, sf::Vector2u(32, 32), std::move(level), 32, 26)) {
    std::cout << "Couldn't load tileset " + TILESET_MAP << std::endl;
  }
}

game::~game() { window_->close(); }

void game::render() {
  window_->clear();
  window_->draw(*map_);
  window_->draw(*player_);
  window_->display();
}

void game::update(sf::Time deltaTime) {
  if (sf::Joystick::isConnected(0)) {
    // get stick position in [-100.0, +100.0]
    float p_x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
    float p_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

    // neutral position is not always zer0
    constexpr float min_axis = 15.;
    if (std::abs(p_x) < min_axis) p_x = 0.;
    if (std::abs(p_y) < min_axis) p_y = 0.;

    // change position of player
    if ((p_x != 0.) || (p_y != 0.)) {
      auto current_pos = player_->getPosition();
      constexpr float max_axis_pos = 100.;
      constexpr float max_speed = 200.;
      const float max_distance = max_speed * deltaTime.asSeconds() / max_axis_pos;

      sf::Vector2f new_pos{current_pos.x + p_x * max_distance, current_pos.y + p_y * max_distance};
      if (map_->isAccessable(new_pos)) {
        player_->updatePosition(new_pos);
      }
    }
  }
}

void game::events() {
  sf::Event event;
  while (window_->pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        running = false;
        break;

      case sf::Event::Resized:
        break;

      case sf::Event::KeyPressed:
        // close window when pressing escape
        if (event.key.code == sf::Keyboard::Escape) {
          running = false;
          break;
        }
        break;

      case sf::Event::MouseMoved:
        // update player position with mouse movement
        player_->updatePosition(window_->mapPixelToCoords({event.mouseMove.x, event.mouseMove.y}));

      default:
        break;
    }
  }
}

bool game::isRunning() { return running; }

}  // namespace mygame