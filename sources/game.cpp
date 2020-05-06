#include "game.h"

#include <assert.h>

#include <cmath>
#include <iostream>

#include "project_headers.h"
#include "tilemap.h"

namespace mygame {

game::game(std::unique_ptr<sf::RenderWindow> window, std::unique_ptr<Player> player, std::unique_ptr<tilemap> map)
    : window_(std::move(window)),
      map_(std::move(map)),
      player_(std::move(player)),
      player_position{20, 20},
      player_size_(1.),
      player_size_factor_(0.1),
      running(true) {
  assert(window_);
  assert(player_);
  assert(map_);
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

    player_->update({p_x, p_y}, deltaTime);
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

      case sf::Event::JoystickButtonPressed:
        if (event.joystickButton.button == 0) {
          auto pos = player_->getPosition();
          pos.x += 32 + 1;
          pos.x += 16;
          map_->destroyTerrain(pos);
        }
        break;

      case sf::Event::MouseMoved: {
        // update player position with mouse movement
        sf::Vector2f new_pos = window_->mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        if (map_->isAccessable(new_pos)) {
          player_->updatePosition(new_pos);
        }
        break;
      }

      default:
        break;
    }
  }
}

bool game::isRunning() { return running; }

}  // namespace mygame