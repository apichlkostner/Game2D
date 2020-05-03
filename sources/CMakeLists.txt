cmake_minimum_required(VERSION 3.5)

# add the executable
add_executable(game main.cpp)

# SFML >= 2.5 uses config of package, if not found: set SFML_DIR
# SFML <  2.5 has a find script, e.g. in /usr/share/SFML/cmake/Modules/FindSFML.cmake
find_package(SFML 2 REQUIRED network audio graphics window system)

target_link_libraries(game  PUBLIC sfml-graphics
                            PUBLIC sfml-audio
                            PUBLIC sfml-window
                            PUBLIC sfml-system)


target_include_directories(game PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

# add the install targets
install(TARGETS game DESTINATION bin)
