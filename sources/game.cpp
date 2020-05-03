
#include "game.h"

#include <assert.h>

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

void game::render() {
  window_->clear();
  window_->draw(*player_);
  window_->display();
}

game::~game() { window_->close(); }

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
        if (event.key.code == sf::Keyboard::R) color_.r += 1;
        if (event.key.code == sf::Keyboard::G) color_.g += 1;
        if (event.key.code == sf::Keyboard::B) color_.b += 1;
        if (event.key.code == sf::Keyboard::Escape) {
          running = false;
          break;
        }
        
        player_->setFillColor(color_);
        break;

      case sf::Event::MouseMoved:
        player_->updatePosition(window_->mapPixelToCoords({event.mouseMove.x, event.mouseMove.y}));

      default:
        break;
    }
  }
}

bool game::isRunning() { return running; }

}  // namespace mygame