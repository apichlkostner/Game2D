
#include "game.h"

#include <iostream>

#include "project_headers.h"

namespace mygame {

game::game(std::unique_ptr<sf::RenderWindow> mwindow)
    : window(std::move(mwindow)), shape(std::make_unique<sf::CircleShape>(100)), running(true) {
  shape->setFillColor(color);
}

void game::render() {
  window->clear();
  window->draw(*shape);
  window->display();
}

game::~game() { window->close(); }

void game::events() {
  sf::Event event;
  while (window->pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        running = false;
        break;

      case sf::Event::Resized:
        break;

      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::R) color.r += 1;
        if (event.key.code == sf::Keyboard::G) color.g += 1;
        if (event.key.code == sf::Keyboard::B) color.b += 1;
        if (event.key.code == sf::Keyboard::Escape) {
          running = false;
          break;
        }
        std::cout << "Color = (" << static_cast<uint32_t>(color.r) << ", " << static_cast<uint32_t>(color.g) << ", "
                  << static_cast<uint32_t>(color.b) << ")" << std::endl;
        shape->setFillColor(color);
        break;

      default:
        break;
    }
  }
}

bool game::isRunning() { return running; }

}  // namespace mygame