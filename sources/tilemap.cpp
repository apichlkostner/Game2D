#include "tilemap.h"

#include <assert.h>

#include <iostream>

namespace mygame {

bool tilemap::load(const std::string& path, sf::Vector2u tile_size, const std::vector<tiletype_t> map,
                   sf::Vector2u mapSizeTiles) {
  if (!tileset_.loadFromFile(path)) return false;

  // save map size for collision check
  map_size_pixel_ = {static_cast<float>(tile_size.x * mapSizeTiles.x),
                     static_cast<float>(tile_size.y * mapSizeTiles.y)};
  map_size_tiles_ = mapSizeTiles;
  tile_size_ = tile_size;
  map_ = std::move(map);

  update();

  return true;
}

void tilemap::update() {
  vertices_.setPrimitiveType(sf::Quads);
  vertices_.resize(map_size_tiles_.x * map_size_tiles_.y * 4);

  for (uint32_t i = 0; i < map_size_tiles_.x; ++i)
    for (uint32_t j = 0; j < map_size_tiles_.y; ++j) {
      uint32_t tileNumber = map_[i + j * map_size_tiles_.x];

      // position of texture
      uint32_t tu = tileNumber % (tileset_.getSize().x / tile_size_.x);
      uint32_t tv = tileNumber / (tileset_.getSize().x / tile_size_.x);

      // postiion of current quad
      sf::Vertex* quad = &vertices_[(i + j * map_size_tiles_.x) * 4];

      // quad position
      quad[0].position = sf::Vector2f(i * tile_size_.x, j * tile_size_.y);
      quad[1].position = sf::Vector2f((i + 1) * tile_size_.x, j * tile_size_.y);
      quad[2].position = sf::Vector2f((i + 1) * tile_size_.x, (j + 1) * tile_size_.y);
      quad[3].position = sf::Vector2f(i * tile_size_.x, (j + 1) * tile_size_.y);

      // quad texture coordinates
      quad[0].texCoords = sf::Vector2f(tu * tile_size_.x, tv * tile_size_.y);
      quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size_.x, tv * tile_size_.y);
      quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size_.x, (tv + 1) * tile_size_.y);
      quad[3].texCoords = sf::Vector2f(tu * tile_size_.x, (tv + 1) * tile_size_.y);
    }
}

bool tilemap::isAccessable(sf::Vector2f pos) const {
  bool isInsideWindow = !((pos.x < 0) || (pos.y < 0) || (pos.x > map_size_pixel_.x) || (pos.y > map_size_pixel_.y));

  bool retValue = isInsideWindow;

  if (isInsideWindow) {
    // check for collision with surrounding tiles
    uint32_t map_x = pos.x / tile_size_.x;
    uint32_t map_y = pos.y / tile_size_.y;

    uint32_t pos_in_map = map_x + (map_y * map_size_tiles_.x);
    assert(pos_in_map < map_.size());
    auto tile_type = map_[pos_in_map];

    // accessible tile types
    retValue = (tile_type == tile_type_grass) || (tile_type == tile_type_sand);
  }

  return retValue;
}

void tilemap::destroyTerrain(sf::Vector2f pos) {
  uint32_t map_x = pos.x / tile_size_.x;
  uint32_t map_y = pos.y / tile_size_.y;
  uint32_t pos_in_map = map_x + (map_y * map_size_tiles_.x);

  map_[pos_in_map] = tile_type_grass;

  update();
}

void tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  states.texture = &tileset_;

  target.draw(vertices_, states);
}

}  // namespace mygame