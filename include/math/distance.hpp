#ifndef RAYKASTER_DISTANCE_HPP
#define RAYKASTER_DISTANCE_HPP

#include <cmath>

#include <SFML/Graphics.hpp>

namespace rk {
    inline float distance(sf::Vector2f lhs, sf::Vector2f rhs) {
        return std::sqrt(std::pow(lhs.x - rhs.x, 2) +
                         std::pow(lhs.y - rhs.y, 2));
    }
}  // namespace rk

#endif
