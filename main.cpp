#include "engine/engine.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  static constexpr auto MAP_PATH = "map.txt";
  rk::Engine engine(MAP_PATH);
  while (engine.is_running()) {
    engine.update();
  }
  return 0;
}
