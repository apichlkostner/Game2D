#ifndef GAME_H
#define GAME_H

#include <memory>

#include "project_headers.h"

namespace mygame {

class game {
 public:
  game(std::unique_ptr<sf::RenderWindow> window, std::unique_ptr<sf::Shape> player);
  ~game();
  void render();
  void events();

  bool isRunning();

 private:
  std::unique_ptr<sf::RenderWindow> window_;
  std::unique_ptr<sf::Shape> player_;
  sf::Color color_{sf::Color::Blue};
  sf::Vector2f player_position;
  float player_size_;
  float player_size_factor_;
  bool running;
};

}  // namespace mygame
#endif