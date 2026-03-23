#pragma once

#include "backend/assets/asset_store.hpp"
#include "backend/font/font.hpp"
#include "backend/texture/texture.hpp"
#include "identifiers.hpp"
#include <memory>

class Assets
{
  public:
    Assets()
    {
        m_textures.add(TextureID::Noodle,
                       std::make_unique<Texture>("assets/images/noodle.png"));
        m_textures.add(TextureID::Pistol,
                       std::make_unique<Texture>("assets/images/pistol.png"));
        m_textures.add(TextureID::Carter,
                       std::make_unique<Texture>("assets/images/carter.png"));
        m_textures.add(
            TextureID::PistolSmall,
            std::make_unique<Texture>("assets/images/pistol_small.png"));
        m_textures.add(
            TextureID::Character,
            std::make_unique<Texture>("assets/images/character.png"));

        m_fonts.add(FontID::Test,
                    std::make_unique<Font>("assets/images/fonts/test.png"));
    }

    const AssetStore<TextureIDKey, Texture> &textures() const
    {
        return m_textures;
    }
    const AssetStore<FontIDKey, Font> &fonts() const { return m_fonts; }

  private:
    AssetStore<TextureIDKey, Texture> m_textures;
    AssetStore<FontIDKey, Font> m_fonts;
};
