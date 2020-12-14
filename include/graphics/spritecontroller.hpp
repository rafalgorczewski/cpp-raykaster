#ifndef RAYKASTER_SPRITECONTROLLER_HPP
#define RAYKASTER_SPRITECONTROLLER_HPP

#include <optional>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "graphics/animation.hpp"

namespace rk {
    enum class AnimationMode { Normal, Immediate };

    class SpriteController {
       public:
        static constexpr auto DEFAULT_MS_PER_NORMAL_FRAME = 20;
        static constexpr auto DEFAULT_MS_PER_IMMEDIATE_FRAME = 15;

        SpriteController(const sf::Texture& texture);

        bool add_animation(const std::string& name, const Animation& animation);
        bool use_animation(
            const std::string& name,
            AnimationMode animation_mode = AnimationMode::Normal,
            sf::Int32 ms_per_frame = DEFAULT_MS_PER_NORMAL_FRAME);
        void update();
        sf::Sprite& get_sprite() & noexcept;
        const sf::Sprite& get_sprite() const& noexcept;
        const sf::Sprite& get_sprite() && = delete;

       private:
        sf::Sprite m_sprite;

        std::unordered_map<std::string, Animation> m_animations;
        std::optional<std::string> m_selected_normal_animation_name{};
        std::optional<std::string> m_selected_immediate_animation_name{};

        sf::Int32 m_ms_per_normal_frame = DEFAULT_MS_PER_NORMAL_FRAME;
        sf::Int32 m_ms_per_immediate_frame = DEFAULT_MS_PER_IMMEDIATE_FRAME;
        sf::Clock m_animation_clock;

        bool animation_already_exists(const std::string& name) const noexcept;
        bool is_normal_animation_set() const noexcept;
        bool is_immediate_animation_active() const noexcept;
        void reset_previous_normal_animation() noexcept;
        void select_as_normal_animation(const std::string& name) noexcept;
        void select_as_immediate_animation(const std::string& name) noexcept;
        void reset_clock() noexcept;
        void update_immediate_animation() noexcept;
        bool are_immediate_frames_left() noexcept;
        void proceed_immediate_animation() noexcept;
        void end_immediate_animation() noexcept;
        void update_normal_animation() noexcept;
        void proceed_normal_animation() noexcept;
        sf::Int32 elapsed_time() const noexcept;
    };
}  // namespace rk

#endif
