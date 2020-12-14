#ifndef RAYKASTER_WINDOW_HPP
#define RAYKASTER_WINDOW_HPP

#include <string>

#include <SFML/Graphics.hpp>

namespace rk {
    class Window : public sf::RenderWindow {
       public:
        Window();
        Window(sf::Vector2u size, const std::string& title);

        void handleEvents() noexcept;

       private:
        inline static const auto DEFAULT_WINDOW_SIZE = sf::Vector2u(1440, 900);
        inline static const auto DEFAULT_WINDOW_NAME = "Window";
        static constexpr auto FRAMERATE_LIMIT = 60;
    };
}  // namespace rk

#endif
