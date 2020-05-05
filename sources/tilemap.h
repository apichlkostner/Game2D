#ifndef TILEMAP_H
#define TILEMAP_H

#include "project_headers.h"

namespace mygame {

enum TileTypes { tile_type_grass, tile_type_water, tile_type_tree, tile_type_rock, tile_type_sand };

class tilemap : public sf::Drawable, public sf::Transformable {
 public:
  bool load(const std::string& path, sf::Vector2u tileSize, const std::vector<uint8_t> map, sf::Vector2u mapSizeTiles);
  void update();
  void destroyTerrain(sf::Vector2f pos);
  bool isAccessable(sf::Vector2f pos);

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  std::vector<uint8_t> map_;
  sf::VertexArray vertices_;
  sf::Texture tileset_;
  sf::Vector2f map_size_pixel_;
  sf::Vector2u map_size_tiles_;
  sf::Vector2u tile_size_;
};

}  // namespace mygame

#endif