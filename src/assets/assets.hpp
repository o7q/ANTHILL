#pragma once

#include "assets/font_ids.hpp"
#include "assets/sound_ids.hpp"
#include "assets/texture_ids.hpp"
#include "backend/assets/asset_store.hpp"
#include "backend/font/font.hpp"
#include "backend/sound/sound.hpp"
#include "backend/texture/texture.hpp"

class Assets
{
  public:
    Assets();

    void initTextures();
    void initSounds();
    void initFonts();

    const AssetStore<TextureIDKey, Texture> &textures() const
    {
        return m_textures;
    }
    const AssetStore<FontIDKey, Font> &fonts() const { return m_fonts; }

  private:
    AssetStore<TextureIDKey, Texture> m_textures;
    AssetStore<FontIDKey, Font> m_fonts;
    AssetStore<SoundIDKey, Sound> m_sounds;
};
