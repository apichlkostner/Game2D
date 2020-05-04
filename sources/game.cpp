
#include "game.h"

#include <assert.h>

#include <cmath>
#include <iostream>

#include "project_headers.h"

namespace mygame {

game::game(std::unique_ptr<sf::RenderWindow> window, std::unique_ptr<Player> player)
    : window_(std::move(window)),
      player_(std::move(player)),
      player_position{20, 20},
      player_size_(1.),
      player_size_factor_(0.1),
      running(true) {
  assert(window_);
  assert(player_);

  player_->setFillColor(color_);
}

game::~game() { window_->close(); }

void game::render() {
  window_->clear();
  window_->draw(*player_);
  window_->display();
}

void game::update(sf::Time deltaTime) {
  if (sf::Joystick::isConnected(0)) {
    // get stick position in [-100.0, +100.0]
    float p_x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
    float p_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

    // neutral position is not always zer0
    constexpr float min_axis = 10.;
    if (std::abs(p_x) < min_axis) p_x = 0.;
    if (std::abs(p_y) < min_axis) p_y = 0.;

    // change position of player
    if ((p_x != 0.) || (p_y != 0.)) {
      auto current_pos = player_->getPosition();
      constexpr float max_axis_pos = 100.;
      constexpr float max_speed = 200.;
      const float max_distance = max_speed * deltaTime.asSeconds() / max_axis_pos;
      player_->updatePosition({current_pos.x + p_x * max_distance, current_pos.y + p_y * max_distance});
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
        // change color, for testing
        if (event.key.code == sf::Keyboard::R) color_.r += 1;
        if (event.key.code == sf::Keyboard::G) color_.g += 1;
        if (event.key.code == sf::Keyboard::B) color_.b += 1;

        // close window when pressing escape
        if (event.key.code == sf::Keyboard::Escape) {
          running = false;
          break;
        }

        player_->setFillColor(color_);
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