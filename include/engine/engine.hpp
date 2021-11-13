#ifndef HQR_INCLUDE_ENGINE_ENGINE_HPP
#define HQR_INCLUDE_ENGINE_ENGINE_HPP

#include <string_view>
#include <vector>

#include "graphics/window.hpp"
#include "math/to_radians.hpp"
#include "memory/observer_ptr.hpp"

namespace rk {
  class Engine {
   public:
    Engine(std::string_view map_path);

    bool is_running() const;
    void update();

   private:
    static constexpr auto WIN_WIDTH = 1200;
    static constexpr auto WIN_HEIGHT = 900;
    static constexpr auto WIN_NAME = "Raykaster";
    static constexpr auto FOV = to_radians(75.0f);
    static constexpr auto RAY_ANGLE_MULTIPLIER =
      FOV / static_cast<float>(WIN_WIDTH);
    static constexpr auto MOVEMENT_ANGLE_CORRECTION_FACTOR = to_radians(22.5);
    static constexpr auto MOVEMENT_SPEED = 0.1f;
    static constexpr auto ROTATION_SPEED = 0.025f;
    static constexpr auto RAY_JUMP_DISTANCE = 0.15f;
    static constexpr auto TEXTURES_CONFIG_PATH = "res/textures.txt";
    static inline const auto FLOOR_COLOUR = sf::Color(165, 42, 42);
    static inline const auto ROOF_COLOUR = sf::Color::Black;

    void initialize();
    void load_map(std::string_view map_path);

    void clear_window();
    void draw();
    void cast_rays();
    void cast_rays_towards_drawables();
    void update_animations();
    void handle_events();
    void player_rotate_left();
    void player_rotate_right();
    void player_move_forward();
    void player_move_backward();
    void display();

    rk::Window m_window{ { WIN_WIDTH, WIN_HEIGHT }, WIN_NAME };
  };  // namespace rk
}  // namespace rk

#endif  // HQR_INCLUDE_ENGINE_ENGINE_HPP
