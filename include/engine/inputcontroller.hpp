#ifndef RAYKASTER_INPUTCONTROLLER_HPP
#define RAYKASTER_INPUTCONTROLLER_HPP

#include <functional>
#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>

#include "engine/icontroller.hpp"

namespace rk {
    class InputController : public IController {
       public:
        using KeyType = sf::Keyboard::Key;

        void start() override;
        void update() override;
        void add_keypress_behaviour(KeyType key,
                                    ControllerCallback update_callback);

       private:
        std::vector<std::pair<KeyType, ControllerCallback>>
            m_key_callback_pairs;
    };
}  // namespace rk

#endif
