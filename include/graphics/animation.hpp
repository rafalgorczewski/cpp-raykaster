#ifndef RAYKASTER_ANIMATION_HPP
#define RAYKASTER_ANIMATION_HPP

#include <SFML/Graphics.hpp>

namespace rk {
    class Animation {
       public:
        Animation() = default;
        Animation(sf::Vector2i tile_starting_position,
                  sf::Vector2i tile_size,
                  int tile_count);

        sf::IntRect get_current_tile() const noexcept;
        void change_tile_to_next() noexcept;
        void reset_animation() noexcept;
        int tiles_left_for_full_sequence() const noexcept;

       private:
        const sf::Vector2i m_tile_starting_position{};
        const sf::Vector2i m_tile_size{};
        const int m_tile_count{};

        int m_current_tile_number{};
    };
}  // namespace rk

#endif
