#ifndef RAYKASTER_ICONTROLLER_HPP
#define RAYKASTER_ICONTROLLER_HPP

#include <functional>

namespace rk {
    struct IController {
        using ControllerCallback = std::function<void(void)>;

        virtual ~IController() = default;
        virtual void start() = 0;
        virtual void update() = 0;
    };
}  // namespace rk

#endif
