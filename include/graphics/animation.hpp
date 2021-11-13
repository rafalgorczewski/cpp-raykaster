#ifndef HQR_INCLUDE_GRAPHICS_ANIMATION_HPP
#define HQR_INCLUDE_GRAPHICS_ANIMATION_HPP

#include <SFML/Graphics.hpp>

namespace rk {
  class Animation {
   public:
    Animation() = default;
    Animation(sf::Vector2i tile_starting_position,
              sf::Vector2i tile_size,
              int tile_count);

    sf::IntRect get_current_tile() const;
    void change_tile_to_next();
    void reset_animation();
    int tiles_left_for_full_sequence() const;

   private:
    const sf::Vector2i m_tile_starting_position{};
    const sf::Vector2i m_tile_size{};
    const int m_tile_count{};

    int m_current_tile_number{};
  };
}  // namespace rk

#endif  // HQR_INCLUDE_GRAPHICS_ANIMATION_HPP
