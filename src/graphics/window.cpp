#include "graphics/window.hpp"

#include <string>

#include <SFML/Graphics.hpp>

namespace rk {
  Window::Window() : Window(DEFAULT_WINDOW_SIZE, DEFAULT_WINDOW_NAME) {
  }

  Window::Window(sf::Vector2u size, const std::string& title)
      : sf::RenderWindow(
          { size.x, size.y }, title, sf::Style::Titlebar | sf::Style::Close) {
    setFramerateLimit(FRAMERATE_LIMIT);
  }

  void Window::handleEvents() {
    sf::Event event{};
    while (pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        close();
      }
    }
  }
}  // namespace rk
