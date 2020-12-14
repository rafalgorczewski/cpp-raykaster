#include <SFML/Graphics.hpp>

#include "graphics/animation.hpp"

namespace rk {
    Animation::Animation(sf::Vector2i tile_starting_position,
                         sf::Vector2i tile_size,
                         int tile_count)
        : m_tile_starting_position{ tile_starting_position },
          m_tile_size{ tile_size },
          m_tile_count{ tile_count } {
    }

    sf::IntRect Animation::get_current_tile() const noexcept {
        return sf::IntRect{ { m_tile_starting_position.x +
                                  (m_current_tile_number * m_tile_size.x),
                              m_tile_starting_position.y },
                            { m_tile_size } };
    }

    void Animation::change_tile_to_next() noexcept {
        if (m_current_tile_number >= m_tile_count - 1) {
            m_current_tile_number = 0;
        } else {
            ++m_current_tile_number;
        }
    }

    void Animation::reset_animation() noexcept {
        m_current_tile_number = 0;
    }

    int Animation::tiles_left_for_full_sequence() const noexcept {
        return (m_tile_count - 1) - m_current_tile_number;
    }
}  // namespace rk
