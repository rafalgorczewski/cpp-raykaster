#ifndef RAYKASTER_ENGINE_HPP
#define RAYKASTER_ENGINE_HPP

#include <string_view>
#include <vector>

#include "engine/icontroller.hpp"
#include "engine/inputcontroller.hpp"
#include "graphics/window.hpp"
#include "math/to_radians.hpp"
#include "memory/observer_ptr.hpp"

namespace rk {
    class Engine {
       public:
        Engine(std::string_view map_path);

        bool is_running() const noexcept;
        void update();

       private:
        static constexpr auto WIN_WIDTH = 1200;
        static constexpr auto WIN_HEIGHT = 900;
        static constexpr auto WIN_NAME = "Raykaster";
        static constexpr auto FOV = to_radians(75.0f);
        static constexpr auto RAY_ANGLE_MULTIPLIER =
            FOV / static_cast<float>(WIN_WIDTH);
        static constexpr auto MOVEMENT_ANGLE_CORRECTION_FACTOR =
            to_radians(22.5);
        static constexpr auto MOVEMENT_SPEED = 0.1f;
        static constexpr auto ROTATION_SPEED = 0.025f;
        static constexpr auto RAY_JUMP_DISTANCE = 0.15f;
        static constexpr auto TEXTURES_CONFIG_PATH = "res/textures.txt";
        static inline const auto FLOOR_COLOUR = sf::Color(165, 42, 42);
        static inline const auto ROOF_COLOUR = sf::Color::Black;

        void initialize();
        void initialize_input_controller_callbacks();

        void load_map(std::string_view map_path);

        void clear_window() noexcept;
        void draw() noexcept;
        void cast_rays() noexcept;
        void cast_rays_towards_drawables();
        void update_animations();
        void handle_events() noexcept;
        void handle_controllers() noexcept;
        void player_rotate_left() noexcept;
        void player_rotate_right() noexcept;
        void player_move_forward();
        void player_move_backward();
        void display() noexcept;

        rk::Window m_window{ { WIN_WIDTH, WIN_HEIGHT }, WIN_NAME };

        InputController m_input_controller;

        std::vector<observer_ptr<IController>> m_controllers = {
            observer_ptr<IController>(&m_input_controller)
        };
    };  // namespace rk
}  // namespace rk

#endif
