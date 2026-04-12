#include "backend/texture/texture.hpp"
#include "assets.hpp"
#include "identifiers/assets/textures.hpp"
#include <memory>
#include <unordered_map>

void Assets::initTextures()
{
    std::unordered_map<TextureIDKey, TextureLoadData> textures;

    textures[TextureID::SandBackground] = {
        "assets/textures/backgrounds/sand.png"};
    textures[TextureID::SandBackground2] = {
        "assets/textures/backgrounds/sand2.png"};

    for (auto &[id, data] : textures)
    {
        m_textures.add(id, std::make_unique<Texture>(data.path));
    }
}
