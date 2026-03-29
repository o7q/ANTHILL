#include "assets.hpp"

void Assets::initTextures()
{
    m_textures.add(TextureID::Noodle,
                   std::make_unique<Texture>("assets/images/noodle.png"));
    m_textures.add(TextureID::Pistol,
                   std::make_unique<Texture>("assets/images/pistol.png"));
    m_textures.add(TextureID::Carter,
                   std::make_unique<Texture>("assets/images/carter.png"));
    m_textures.add(TextureID::PistolSmall,
                   std::make_unique<Texture>("assets/images/pistol_small.png"));
    m_textures.add(TextureID::Character,
                   std::make_unique<Texture>("assets/images/character.png"));
    m_textures.add(TextureID::TheMan,
                   std::make_unique<Texture>("assets/images/the_man.png"));
    m_textures.add(TextureID::TheMan2,
                   std::make_unique<Texture>("assets/images/the_man2.png"));
}
