#ifndef TILEMAP_H
#define TILEMAP_H

#include "project_headers.h"

namespace mygame {

class tilemap : public sf::Drawable, public sf::Transformable {
 public:
  bool load(const std::string& path, sf::Vector2u tileSize, const int* map, uint32_t width, uint32_t height);

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::VertexArray vertices_;
  sf::Texture tileset_;
};

}  // namespace mygame

#endif