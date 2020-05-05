#ifndef PLAYER_H
#define PLAYER_H

#include "project_headers.h"
#include "config.h"

namespace mygame {

class Player : public sf::Sprite {
 public:
  Player() : size_faktor_(1.0), size_faktor_delta_(0.05) {
    if (!texture.loadFromFile(TEXTURE_FILE_PLAYER)) {
      throw std::runtime_error("Texture file " + TEXTURE_FILE_PLAYER + " couldn't be loaded");
    }
    this->setTexture(texture);
  }

  void updatePosition(sf::Vector2f pos) {
    setPosition(pos);

    if (size_faktor_ > 1.05)
      size_faktor_delta_ = -0.005;
    else if (size_faktor_ < 0.95)
      size_faktor_delta_ = 0.005;

    size_faktor_ += size_faktor_delta_;

    setScale({size_faktor_, size_faktor_});
  }

 private:
  float size_faktor_;
  float size_faktor_delta_;
  sf::Texture texture;
};

}  // namespace mygame

#endif