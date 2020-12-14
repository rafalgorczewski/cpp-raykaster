#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

#include <spdlog/spdlog.h>

#include <SFML/Graphics.hpp>

#include "graphics/texturemanager.hpp"
#include "memory/observer_ptr.hpp"

namespace rk {
    bool TextureManager::load_textures(
        std::string textures_configuration_path) {
        if (!m_textures_loaded) {
            std::ifstream textures_config_stream(textures_configuration_path);
            if (!textures_config_stream.is_open()) {
                spdlog::error("Texture Manager: File '{}' could not be opened.",
                              textures_configuration_path);
                return false;
            }
            for (std::string texture_name, texture_path;
                 std::getline(textures_config_stream, texture_name, ',') &&
                 std::getline(textures_config_stream, texture_path);) {
                load_texture(texture_name, texture_path);
            }

            m_textures_loaded = true;
        }
        return true;
    }

    void TextureManager::load_texture(std::string name, std::string path) {
        if (auto texture = sf::Texture(); !texture.loadFromFile(path)) {
            m_textures_map[name] = texture;
        } else {
            spdlog::error(
                "Texture Manager: Could not load texture: '{}' from: '{}'",
                name,
                path);
        }
    }

    sf::Texture& TextureManager::get_texture(std::string name) & {
        if (auto it = m_textures_map.find(name); it != m_textures_map.end()) {
            return (*it).second;
        }

        spdlog::error("Texture Manager: Trying to use unknown texture: '{}'",
                      name);

        m_textures_map[name] = {};
        return (m_textures_map[name]);
    }
}  // namespace rk
