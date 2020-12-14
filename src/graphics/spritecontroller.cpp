#include <optional>
#include <string>
#include <unordered_map>

#include <spdlog/spdlog.h>

#include <SFML/Graphics.hpp>

#include "graphics/animation.hpp"
#include "graphics/spritecontroller.hpp"

namespace rk {
    SpriteController::SpriteController(const sf::Texture& texture)
        : m_sprite(texture) {
    }

    bool SpriteController::add_animation(const std::string& name,
                                         const Animation& animation) {
        if (animation_already_exists(name)) {
            spdlog::error(
                "Sprite Controller: There is already an animation called: '{}'",
                name);
            return false;
        }
        m_animations.emplace(name, animation);

        return true;
    }

    bool SpriteController::use_animation(const std::string& name,
                                         AnimationMode animation_mode,
                                         sf::Int32 ms_per_frame) {
        if (!animation_already_exists(name)) {
            spdlog::error(
                "Sprite Controller: There is no animation to use "
                "called: '{}'",
                name);
            return false;
        }
        if (animation_mode == AnimationMode::Normal) {
            m_ms_per_normal_frame = ms_per_frame;
            reset_previous_normal_animation();
            select_as_normal_animation(name);
            reset_clock();
        } else if (animation_mode == AnimationMode::Immediate) {
            m_ms_per_immediate_frame = ms_per_frame;
            select_as_immediate_animation(name);
            reset_clock();
        }
        return true;
    }

    void SpriteController::update() {
        if (!is_normal_animation_set()) {
            spdlog::error(
                "Sprite Controller: No animation was set before update");
        } else {
            if (is_immediate_animation_active()) {
                update_immediate_animation();
            } else {
                update_normal_animation();
            }
        }
    }

    sf::Sprite& SpriteController::get_sprite() & noexcept {
        return m_sprite;
    }

    const sf::Sprite& SpriteController::get_sprite() const& noexcept {
        return m_sprite;
    }

    bool SpriteController::animation_already_exists(
        const std::string& name) const noexcept {
        return m_animations.find(name) != m_animations.end();
    }

    bool SpriteController::is_normal_animation_set() const noexcept {
        return !!m_selected_normal_animation_name;
    }

    bool SpriteController::is_immediate_animation_active() const noexcept {
        return !!m_selected_immediate_animation_name;
    }

    void SpriteController::reset_previous_normal_animation() noexcept {
        if (m_selected_normal_animation_name) {
            m_animations[*m_selected_normal_animation_name].reset_animation();
        }
    }

    void SpriteController::select_as_normal_animation(
        const std::string& name) noexcept {
        m_selected_normal_animation_name = name;
        m_sprite.setTextureRect(
            m_animations[*m_selected_normal_animation_name].get_current_tile());
    }

    void SpriteController::select_as_immediate_animation(
        const std::string& name) noexcept {
        m_selected_immediate_animation_name = name;
        m_sprite.setTextureRect(
            m_animations[*m_selected_immediate_animation_name]
                .get_current_tile());
    }

    void SpriteController::reset_clock() noexcept {
        m_animation_clock.restart();
    }

    void SpriteController::update_immediate_animation() noexcept {
        if (elapsed_time() >= m_ms_per_immediate_frame) {
            if (are_immediate_frames_left()) {
                proceed_immediate_animation();
            } else {
                end_immediate_animation();
            }
            reset_clock();
        }
    }

    bool SpriteController::are_immediate_frames_left() noexcept {
        return m_animations[*m_selected_immediate_animation_name]
            .tiles_left_for_full_sequence();
    }

    void SpriteController::proceed_immediate_animation() noexcept {
        m_animations[*m_selected_immediate_animation_name]
            .change_tile_to_next();
        m_sprite.setTextureRect(
            m_animations[*m_selected_immediate_animation_name]
                .get_current_tile());
    }

    void SpriteController::end_immediate_animation() noexcept {
        m_animations[*m_selected_immediate_animation_name].reset_animation();
        m_selected_immediate_animation_name.reset();
        m_animations[*m_selected_normal_animation_name].change_tile_to_next();
        m_sprite.setTextureRect(
            m_animations[*m_selected_normal_animation_name].get_current_tile());
    }

    void SpriteController::update_normal_animation() noexcept {
        if (elapsed_time() >= m_ms_per_normal_frame) {
            proceed_normal_animation();
            reset_clock();
        }
    }

    void SpriteController::proceed_normal_animation() noexcept {
        m_animations[*m_selected_normal_animation_name].change_tile_to_next();
        m_sprite.setTextureRect(
            m_animations[*m_selected_normal_animation_name].get_current_tile());
    }

    sf::Int32 SpriteController::elapsed_time() const noexcept {
        return m_animation_clock.getElapsedTime().asMilliseconds();
    }
}  // namespace rk
