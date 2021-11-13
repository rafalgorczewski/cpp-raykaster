#ifndef HQR_INCLUDE_MATH_TO_RADIANS_HPP
#define HQR_INCLUDE_MATH_TO_RADIANS_HPP

#include <cmath>

namespace rk {
  inline constexpr float to_radians(float deg) {
    return (deg * M_PI) / 180.0f;
  }
}  // namespace rk

#endif  // HQR_INCLUDE_MATH_TO_RADIANS_HPP
