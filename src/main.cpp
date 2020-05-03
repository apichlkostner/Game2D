#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>



int main() {
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  window.setPosition(sf::Vector2i(500, 300));
  window.setVerticalSyncEnabled(true);
  //window.setActive(true);

  float radius = 100.f;
  sf::CircleShape shape(radius);
  sf::Color color(sf::Color::Green);
  shape.setFillColor(color);

  bool running = true;
  while (running) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          running = false;
          break;

          case sf::Event::Resized:
          radius = std::min(event.size.width, event.size.height) / 2.f;
          //shape.setRadius(radius);
          //glViewport(0, 0, event.size.width, event.size.height);
          break;

        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::R) color.r += 1;
          if (event.key.code == sf::Keyboard::G) color.g += 1;
          if (event.key.code == sf::Keyboard::B) color.b += 1;
          if (event.key.code == sf::Keyboard::Escape) {
            running = false;
            break;
          }
          std::cout << "Color = (" << static_cast<uint32_t>(color.r) << ", "
                    << static_cast<uint32_t>(color.g) << ", "
                    << static_cast<uint32_t>(color.b) << ")" << std::endl;
          shape.setFillColor(color);
          break;

        default:
          break;
      }
    }

    window.clear();
    window.draw(shape);
    window.display();
  }

  window.close();

  return 0;
}