#ifndef HQR_INCLUDE_GRAPHICS_WINDOW_HPP
#define HQR_INCLUDE_GRAPHICS_WINDOW_HPP

#include <string>

#include <SFML/Graphics.hpp>

namespace rk {
  class Window : public sf::RenderWindow {
   public:
    Window();
    Window(sf::Vector2u size, const std::string& title);

    void handleEvents();

   private:
    inline static const auto DEFAULT_WINDOW_SIZE = sf::Vector2u(1440, 900);
    inline static const auto DEFAULT_WINDOW_NAME = "Window";
    static constexpr auto FRAMERATE_LIMIT = 60;
  };
}  // namespace rk

#endif  // HQR_INCLUDE_GRAPHICS_WINDOW_HPP
