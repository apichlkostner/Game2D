#include "tilemap.h"

#include <assert.h>

#include <iostream>

namespace mygame {

bool tilemap::load(const std::string& path, sf::Vector2u tile_size, const std::vector<uint8_t> map,
                   uint32_t map_width_quads, uint32_t map_height_quads) {
  if (!tileset_.loadFromFile(path)) return false;

  // save map size for collision check
  map_size_pixel_ = {static_cast<float>(tile_size.x * map_width_quads),
                     static_cast<float>(tile_size.y * map_height_quads)};
  map_size_tiles_ = {map_width_quads, map_height_quads};
  tile_size_ = tile_size;
  map_ = std::move(map);

  vertices_.setPrimitiveType(sf::Quads);
  vertices_.resize(map_width_quads * map_height_quads * 4);

  for (unsigned int i = 0; i < map_width_quads; ++i)
    for (unsigned int j = 0; j < map_height_quads; ++j) {
      int tileNumber = map_[i + j * map_width_quads];

      // position of texture
      int tu = tileNumber % (tileset_.getSize().x / tile_size.x);
      int tv = tileNumber / (tileset_.getSize().x / tile_size.x);

      // postiion of current quad
      sf::Vertex* quad = &vertices_[(i + j * map_width_quads) * 4];

      // quad position
      quad[0].position = sf::Vector2f(i * tile_size.x, j * tile_size.y);
      quad[1].position = sf::Vector2f((i + 1) * tile_size.x, j * tile_size.y);
      quad[2].position = sf::Vector2f((i + 1) * tile_size.x, (j + 1) * tile_size.y);
      quad[3].position = sf::Vector2f(i * tile_size.x, (j + 1) * tile_size.y);

      // quad texture coordinates
      quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
      quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
      quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
      quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
    }

  return true;
}

bool tilemap::isAccessable(sf::Vector2f pos) {
  bool isInsideWindow = !((pos.x < 0) || (pos.y < 0) || (pos.x > (map_size_pixel_.x - tile_size_.x)) ||
                          (pos.y > (map_size_pixel_.y - tile_size_.y)));

  bool retValue = isInsideWindow;

  if (isInsideWindow) {
    // check for collision with surrounding tiles
    for (uint32_t delta_x = 0; delta_x <= 1; delta_x++) {
      for (uint32_t delta_y = 0; delta_y <= 1; delta_y++) {
        uint32_t map_u = (pos.x + delta_x * tile_size_.x) / tile_size_.x;
        uint32_t map_v = (pos.y + delta_y * tile_size_.y) / tile_size_.y;

        uint32_t pos_in_map = map_u + map_v * map_size_tiles_.x;
        assert(pos_in_map < map_.size());
        auto tile_type = map_[pos_in_map];

        // accessible tile types
        retValue &= (tile_type == tile_type_grass) || (tile_type == tile_type_sand);
      }
    }
  }

  return retValue;
}

void tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  states.texture = &tileset_;

  target.draw(vertices_, states);
}

}  // namespace mygame