#include "assets.hpp"

void Assets::initTextures()
{
    m_textures.add(TextureID::SandBackground,
                   std::make_unique<Texture>("assets/textures/sand.png"));
    m_textures.add(TextureID::Shotgun,
                   std::make_unique<Texture>("assets/textures/shotgun.png"));
}
