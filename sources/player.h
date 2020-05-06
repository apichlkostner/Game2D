#ifndef PLAYER_H
#define PLAYER_H

#include "config.h"
#include "project_headers.h"
#include "tilemap.h"

namespace mygame {

class Player : public sf::Sprite {
 public:
  Player(const tilemap& map);

  void update(sf::Vector2f forece, sf::Time deltaTime);

  void updatePosition(sf::Vector2f pos);

  void accelerate(sf::Vector2f a);

 private:
  float mass_;
  sf::Vector2f velocity_;
  float size_faktor_;
  float size_faktor_delta_;
  sf::Texture texture;
  const tilemap& map_;
};

}  // namespace mygame

#endif