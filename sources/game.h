#ifndef GAME_H
#define GAME_H

#include <memory>
#include "player.h"
#include "project_headers.h"

namespace mygame {

class game {
 public:
  game(std::unique_ptr<sf::RenderWindow> window, std::unique_ptr<Player> player);
  ~game();
  
  void events();
  void update(sf::Time deltaTime);
  void render();
  
  bool isRunning();

 private:
  std::unique_ptr<sf::RenderWindow> window_;
  std::unique_ptr<Player> player_;
  sf::Color color_{sf::Color::Blue};
  sf::Vector2f player_position;
  float player_size_;
  float player_size_factor_;
  bool running;
};

}  // namespace mygame
#endif