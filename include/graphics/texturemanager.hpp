#ifndef RAYKASTER_TEXTUREMANAGER_HPP
#define RAYKASTER_TEXTUREMANAGER_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

namespace rk {
    class TextureManager {
       public:
        bool load_textures(std::string textures_configuration_path);
        sf::Texture& get_texture(std::string name) &;

       private:
        void load_texture(std::string name, std::string path);

        bool m_textures_loaded{};
        std::unordered_map<std::string, sf::Texture> m_textures_map;
    };
}  // namespace rk

#endif
