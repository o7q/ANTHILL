#pragma once

#include "core/asset_pool/asset_pool.hpp"
#include "core/font/font.hpp"
#include "core/sound/sound.hpp"
#include "core/sprite_sheet/sprite_sheet.hpp"
#include "core/texture/texture.hpp"
#include "identifiers/assets/fonts.hpp"
#include "identifiers/assets/sounds.hpp"
#include "identifiers/assets/spritesheet.hpp"
#include "identifiers/assets/textures.hpp"

class Assets
{
  public:
    Assets();

    const AssetPool<TextureID, Texture> &textures() const { return m_textures; }
    const AssetPool<SpriteSheetID, SpriteSheet> &spriteSheets() const { return m_spriteSheets; }
    const AssetPool<FontID, Font> &fonts() const { return m_fonts; }
    const AssetPool<SoundID, Sound> &sounds() const { return m_sounds; }

  private:
    AssetPool<TextureID, Texture> m_textures;
    AssetPool<SpriteSheetID, SpriteSheet> m_spriteSheets;
    AssetPool<FontID, Font> m_fonts;
    AssetPool<SoundID, Sound> m_sounds;
};
