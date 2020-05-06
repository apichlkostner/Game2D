#include "player.h"

#include <iostream>

namespace mygame {
Player::Player(const tilemap& map) : map_(map), size_faktor_(1.0), size_faktor_delta_(0.05), mass_(0.1) {
  if (!texture.loadFromFile(TEXTURE_FILE_PLAYER)) {
    throw std::runtime_error("Texture file " + TEXTURE_FILE_PLAYER + " couldn't be loaded");
  }
  this->setTexture(texture);
}

void Player::update(sf::Vector2f force, sf::Time deltaTime) {
  constexpr float friction = 2.f;
  constexpr float drag = 0.01;
  constexpr float player_width = 25;
  constexpr float obstacle_force = 1.f;
  constexpr float damping = 0.3f;

  force -= velocity_ * friction * mass_;
  
  velocity_ += force / mass_ * deltaTime.asSeconds();
  sf::Vector2f new_position = getPosition() + velocity_ * deltaTime.asSeconds();

  sf::Vector2f pos_top_left = new_position;
  sf::Vector2f pos_top_right = new_position + sf::Vector2f{player_width, 0.f};
  sf::Vector2f pos_bottom_left = new_position + sf::Vector2f{0.f, player_width};
  sf::Vector2f pos_bottom_right = new_position + sf::Vector2f{player_width, player_width};

  // checking for obstacles and adapt positon and velocity accordingly
  if (velocity_.x > 0) {
    if (!map_.isAccessable(pos_top_right) || !map_.isAccessable(pos_bottom_right)) {
      new_position.x = getPosition().x - obstacle_force;
      velocity_.x = -velocity_.x * damping;
    }
  } else if (velocity_.x < 0) {
    if (!map_.isAccessable(pos_top_left) || !map_.isAccessable(pos_bottom_left)) {
      new_position.x = getPosition().x + obstacle_force;
      velocity_.x = -velocity_.x * damping;
    }
  }

  if (velocity_.y > 0) {
    if (!map_.isAccessable(pos_bottom_left) || !map_.isAccessable(pos_bottom_right)) {
      new_position.y = getPosition().y - obstacle_force;
      velocity_.y = -velocity_.y * damping;
    }
  } else if (velocity_.y < 0) {
    if (!map_.isAccessable(pos_top_left) || !map_.isAccessable(pos_top_right)) {
      new_position.y = getPosition().y + obstacle_force;
      velocity_.y = -velocity_.y * damping;
    }
  }

  setPosition(new_position);
}

void Player::accelerate(sf::Vector2f a) {}

void Player::updatePosition(sf::Vector2f pos) {
  setPosition(pos);

  if (size_faktor_ > 1.05)
    size_faktor_delta_ = -0.005;
  else if (size_faktor_ < 0.95)
    size_faktor_delta_ = 0.005;

  size_faktor_ += size_faktor_delta_;

  setScale({size_faktor_, size_faktor_});
}
}  // namespace mygame