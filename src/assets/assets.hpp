#pragma once

#include "backend/assets/asset_store.hpp"
#include "backend/font/font.hpp"
#include "backend/sound/sound.hpp"
#include "backend/texture/texture.hpp"
#include "identifiers/fonts.hpp"
#include "identifiers/sounds.hpp"
#include "identifiers/textures.hpp"

class Assets
{
  public:
    Assets();

    const AssetStore<TextureIDKey, Texture> &textures() const
    {
        return m_textures;
    }
    const AssetStore<FontIDKey, Font> &fonts() const { return m_fonts; }
    const AssetStore<SoundIDKey, Sound> &sounds() const { return m_sounds; }

  private:
    void initTextures();
    void initSounds();
    void initFonts();

  private:
    AssetStore<TextureIDKey, Texture> m_textures;
    AssetStore<FontIDKey, Font> m_fonts;
    AssetStore<SoundIDKey, Sound> m_sounds;
};
