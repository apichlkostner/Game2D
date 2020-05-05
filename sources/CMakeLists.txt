cmake_minimum_required(VERSION 3.5)

# add the executable
add_executable(game main.cpp game.cpp)

# SFML >= 2.5 uses config of package, if not found: set SFML_DIR
# SFML <  2.5 has a find script, e.g. in /usr/share/SFML/cmake/Modules/FindSFML.cmake
find_package(SFML 2 REQUIRED network audio graphics window system)

target_link_libraries(game  PUBLIC sfml-graphics
                            PUBLIC sfml-audio
                            PUBLIC sfml-window
                            PUBLIC sfml-system)

# removed for VSCode CMake plugin bug https://github.com/microsoft/vscode-cmake-tools/issues/1141
#target_precompile_headers(game PRIVATE project_headers.h)

#message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}/include")
target_include_directories(game PRIVATE ${PROJECT_SOURCE_DIR}/include
                                PUBLIC "${PROJECT_BINARY_DIR}"
                           )

# add the install targets
install(TARGETS game DESTINATION bin)
