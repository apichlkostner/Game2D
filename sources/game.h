#ifndef GAME_H
#define GAME_H

#include <memory>

#include "project_headers.h"

namespace mygame {

class game {
 public:
  game(std::unique_ptr<sf::RenderWindow> window);
  ~game();
  void render();
  void events();

  bool isRunning();

 private:
  std::unique_ptr<sf::RenderWindow> window;
  std::unique_ptr<sf::Shape> shape;
  sf::Color color{sf::Color::Green};
  bool running;
};

}  // namespace mygame
#endif