#ifndef CONFIG_H
#define CONFIG_H

#include "project_headers.h"

namespace mygame {

typedef uint8_t tiletype_t;

// delta time for update
const sf::Time TIME_UPDATE = sf::seconds(1. / 60.);

const std::string WINDOW_ICON         = "resources/window_icon.png";

const std::string TEXTURE_FILE_PLAYER = "resources/player.png";
const std::string TILESET_MAP_FILENAME  = "resources/tileset.png";
const sf::Vector2u TILE_SIZE            {32, 32};

const std::string MAP_FILE            = "resources/map2.csv";

}

#endif