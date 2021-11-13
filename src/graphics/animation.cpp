#include "graphics/animation.hpp"

#include <SFML/Graphics.hpp>

namespace rk {
  Animation::Animation(sf::Vector2i tile_starting_position,
                       sf::Vector2i tile_size,
                       int tile_count)
      : m_tile_starting_position{ tile_starting_position },
        m_tile_size{ tile_size },
        m_tile_count{ tile_count } {
  }

  sf::IntRect Animation::get_current_tile() const {
    return sf::IntRect{ { m_tile_starting_position.x +
                            (m_current_tile_number * m_tile_size.x),
                          m_tile_starting_position.y },
                        { m_tile_size } };
  }

  void Animation::change_tile_to_next() {
    if (m_current_tile_number >= m_tile_count - 1) {
      m_current_tile_number = 0;
    } else {
      ++m_current_tile_number;
    }
  }

  void Animation::reset_animation() {
    m_current_tile_number = 0;
  }

  int Animation::tiles_left_for_full_sequence() const {
    return (m_tile_count - 1) - m_current_tile_number;
  }
}  // namespace rk
