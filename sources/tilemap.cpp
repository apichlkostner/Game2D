#include "tilemap.h"

namespace mygame {

bool tilemap::load(const std::string& path, sf::Vector2u tileSize, const int* map, uint32_t width, uint32_t height) {
  if (!tileset_.loadFromFile(path)) return false;

  vertices_.setPrimitiveType(sf::Quads);
  vertices_.resize(width * height * 4);

  for (unsigned int i = 0; i < width; ++i)
    for (unsigned int j = 0; j < height; ++j) {
      int tileNumber = map[i + j * width];

      // position of texture
      int tu = tileNumber % (tileset_.getSize().x / tileSize.x);
      int tv = tileNumber / (tileset_.getSize().x / tileSize.x);

      // postiion of current quad
      sf::Vertex* quad = &vertices_[(i + j * width) * 4];

      // quad position
      quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
      quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
      quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
      quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

      // quad texture coordinates
      quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
      quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
      quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
      quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    }

  return true;
}

void tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  states.texture = &tileset_;

  target.draw(vertices_, states);
}

}  // namespace mygame