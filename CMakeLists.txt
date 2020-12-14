cmake_minimum_required(VERSION 3.12)
project(raykaster)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -O0 -g")

set(RK_INCLUDE_DIRS "include")

include_directories(${RK_INCLUDE_DIRS})

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

set(RK_GRAPHICS_SRC 
    "src/graphics/animation.cpp"
    "src/graphics/spritecontroller.cpp"
    "src/graphics/texturemanager.cpp"
    "src/graphics/window.cpp"
)

set(RK_ENGINE_SRC
    "src/engine/engine.cpp"
    "src/engine/inputcontroller.cpp"
)

add_executable(raykaster main.cpp ${RK_GRAPHICS_SRC} ${RK_ENGINE_SRC})
target_link_libraries(raykaster sfml-graphics)