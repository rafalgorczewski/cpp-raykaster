#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

#include <spdlog/spdlog.h>

#include <SFML/Graphics.hpp>

#include "engine/engine.hpp"
#include "graphics/texturemanager.hpp"
#include "math/distance.hpp"

namespace rk {

    Engine::Engine(std::string_view map_path) {
        initialize();
        load_map(map_path);
    }

    void Engine::initialize() {
        initialize_input_controller_callbacks();
    }

    void Engine::initialize_input_controller_callbacks() {
        m_input_controller.add_keypress_behaviour(
            sf::Keyboard::Left, [this] { player_rotate_left(); });
        m_input_controller.add_keypress_behaviour(
            sf::Keyboard::Right, [this] { player_rotate_right(); });
        m_input_controller.add_keypress_behaviour(
            sf::Keyboard::Up, [this] { player_move_forward(); });
        m_input_controller.add_keypress_behaviour(
            sf::Keyboard::Down, [this] { player_move_backward(); });
    }

    void Engine::load_map(std::string_view map_path) {
        // try {
        //     m_map = Map().from_file(map_path);

        //     auto [spawn_x, spawn_y] = m_map->get_spawnpoint();
        //     m_player.set_position(
        //         { static_cast<float>(spawn_x), static_cast<float>(spawn_y)
        //         });

        // } catch (const std::exception& e) {
        //     std::cerr << e.what() << std::endl;
        // }
    }

    bool Engine::is_running() const noexcept {
        return m_window.isOpen();
    }

    void Engine::update() {
        clear_window();
        draw();
        handle_events();
        handle_controllers();
        display();
    }

    void Engine::clear_window() noexcept {
        m_window.clear(sf::Color::White);

        sf::RectangleShape floor_rect{ { WIN_WIDTH, WIN_HEIGHT / 2 } };
        floor_rect.setFillColor(FLOOR_COLOUR);
        floor_rect.setPosition(0, WIN_HEIGHT / 2);
        m_window.draw(floor_rect);

        sf::RectangleShape roof_rect{ { WIN_WIDTH, WIN_HEIGHT / 2 } };
        floor_rect.setFillColor(ROOF_COLOUR);
        floor_rect.setPosition(0, 0);
        m_window.draw(floor_rect);
    }

    void Engine::draw() noexcept {
        cast_rays();
        cast_rays_towards_drawables();
        update_animations();
    }

    void Engine::cast_rays() noexcept {
        // for (int ray_number = 0; ray_number < WIN_WIDTH; ++ray_number) {
        //     const float current_angle = std::atan(
        //         static_cast<float>(ray_number) * RAY_ANGLE_MULTIPLIER);
        //     const float dir_x =
        //         std::sin(m_player.get_angle_rad() + current_angle);
        //     const float dir_y =
        //         -std::cos(m_player.get_angle_rad() + current_angle);

        //     float x{};
        //     float y{};
        //     float travelled_distance{};
        //     do {
        //         travelled_distance += RAY_JUMP_DISTANCE;
        //         x = m_player.get_position().x + dir_x * travelled_distance;
        //         y = m_player.get_position().y + dir_y * travelled_distance;
        //     } while (!(*m_map)[(int)x][(int)y].is_wall());
        //     travelled_distance *= std::cos(current_angle);

        //     sf::RectangleShape rect{ { 1,
        //                                WIN_HEIGHT / travelled_distance * 2 }
        //                                };
        //     auto color = sf::Color::Black;
        //     color.r = 255 - ((255 - travelled_distance * 30 > 0)
        //                          ? travelled_distance * 30
        //                          : 235);
        //     rect.setFillColor(color);
        //     rect.setPosition(ray_number,
        //                      (WIN_HEIGHT / 2) - (rect.getSize().y / 2));
        //     m_window.draw(rect);
        // }
    }

    void Engine::cast_rays_towards_drawables() {
        // for (auto drawable : m_drawables) {
        //     const float ray_length =
        //         distance(m_player.get_position(), drawable->get_position());
        //     const float dir_x =
        //         (drawable->get_position().x - m_player.get_position().x) /
        //         ray_length;
        //     const float dir_y =
        //         (drawable->get_position().y - m_player.get_position().y) /
        //         ray_length;

        //     float current_x{};
        //     float current_y{};
        //     bool encountered_obstacle{};

        //     float travelled_distance{};
        //     do {
        //         travelled_distance += RAY_JUMP_DISTANCE;
        //         current_x += m_player.get_position().x + dir_x / 10;
        //         current_y += m_player.get_position().y + dir_y / 10;
        //         std::clog << current_x << ", " << current_y << ", "
        //                   << travelled_distance << std::endl;

        //         if ((*m_map)[(int)current_x][(int)current_y].is_wall()) {
        //             encountered_obstacle = true;
        //         }
        //     } while (distance({ current_x, current_y },
        //                       drawable->get_position()) > 0.5 &&
        //              not encountered_obstacle);

        //     if (encountered_obstacle) {
        //         // continue;
        //     }

        //     // calculating angle between player's directional vector and a
        //     // directional vector to the drawable
        //     const float player_dir_x = std::cos(m_player.get_angle_rad());
        //     const float player_dir_y = std::sin(m_player.get_angle_rad());

        //     const float player_dir_length = std::sqrt(
        //         std::pow(player_dir_x, 2) + std::pow(player_dir_y, 2));
        //     const float ray_dir_length =
        //         std::sqrt(std::pow(dir_x, 2) + std::pow(dir_y, 2));

        //     const float dot_product =
        //         (player_dir_x * dir_x) + (player_dir_y * dir_y);

        //     const float angle =
        //         std::acos(dot_product / std::abs(player_dir_length) *
        //                   std::abs(ray_dir_length));

        //     // std::clog << angle << ", " << m_player.get_angle_rad() <<
        //     // std::endl;

        //     drawable->draw(1, { (WIN_WIDTH / 2), (WIN_HEIGHT / 2) },
        //     m_window);
        // }
    }

    void Engine::update_animations() {
    }

    void Engine::handle_events() noexcept {
        m_window.handleEvents();
    }

    void Engine::handle_controllers() noexcept {
        for (auto controller : m_controllers) {
            controller->update();
        }
    }

    void Engine::player_rotate_left() noexcept {
        // m_player.set_angle_rad(m_player.get_angle_rad() - ROTATION_SPEED);
    }

    void Engine::player_rotate_right() noexcept {
        // m_player.set_angle_rad(m_player.get_angle_rad() + ROTATION_SPEED);
    }

    void Engine::player_move_forward() {
        // const auto position = m_player.get_position();

        // const float dir_x = std::sin(m_player.get_angle_rad() +
        //                              MOVEMENT_ANGLE_CORRECTION_FACTOR);
        // const float dir_y = -std::cos(m_player.get_angle_rad() +
        //                               MOVEMENT_ANGLE_CORRECTION_FACTOR);

        // if (auto [future_x, future_y] =
        //         std::pair(position.x + dir_x * MOVEMENT_SPEED,
        //                   position.y + dir_y * MOVEMENT_SPEED);
        //     future_x > 0 && future_y > 0 && future_x <= m_map->get_size().x
        //     && future_y <= m_map->get_size().y &&
        //     not(*m_map)[future_x][future_y].is_wall()) {
        //     //
        //     m_player.set_position({ future_x, future_y });
        //     //
        // }
    }

    void Engine::player_move_backward() {
        // const auto position = m_player.get_position();

        // const float dir_x = std::sin(m_player.get_angle_rad() +
        //                              MOVEMENT_ANGLE_CORRECTION_FACTOR);
        // const float dir_y = -std::cos(m_player.get_angle_rad() +
        //                               MOVEMENT_ANGLE_CORRECTION_FACTOR);

        // if (auto [future_x, future_y] =
        //         std::pair(position.x - dir_x * MOVEMENT_SPEED,
        //                   position.y - dir_y * MOVEMENT_SPEED);
        //     future_x > 0 && future_y > 0 && future_x <= m_map->get_size().x
        //     && future_y <= m_map->get_size().y &&
        //     not(*m_map)[future_x][future_y].is_wall()) {
        //     //
        //     m_player.set_position({ future_x, future_y });
        //     //
        // }
    }

    void Engine::display() noexcept {
        m_window.display();
    }
}  // namespace rk
