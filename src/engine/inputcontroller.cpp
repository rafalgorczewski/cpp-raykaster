#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "engine/inputcontroller.hpp"

namespace rk {
    void InputController::update() {
        for (auto [key, callback] : m_key_callback_pairs) {
            if (sf::Keyboard::isKeyPressed(key)) {
                callback();
            }
        }
    }

    void InputController::add_keypress_behaviour(
        KeyType key, ControllerCallback update_callback) {
        m_key_callback_pairs.emplace_back(key, update_callback);
    }
}  // namespace rk
