#ifndef CONFIG_H
#define CONFIG_H

#include "project_headers.h"

namespace mygame {

// delta time for update
const sf::Time TIME_UPDATE = sf::seconds(1. / 60.);

const std::string TEXTURE_FILE_PLAYER = "resources/player.png";
const std::string TILESET_MAP         = "resources/tileset.png";

}

#endif