#pragma once

#include "asset_pool/asset_pool.hpp"
#include "backend/font/font.hpp"
#include "backend/sound/sound.hpp"
#include "backend/sprite_sheet/sprite_sheet.hpp"
#include "backend/texture/texture.hpp"
#include "identifiers/assets/fonts.hpp"
#include "identifiers/assets/sounds.hpp"
#include "identifiers/assets/spritesheet.hpp"
#include "identifiers/assets/textures.hpp"

class Assets
{
  private:
    struct TextureLoadData
    {
        std::string path = "";
    };

    struct SpriteSheetLoadData
    {
        std::string path = "";
        Vec2u size;
    };

    struct FontLoadData
    {
        std::string path = "";
    };

    struct SoundLoadData
    {
        std::string path = "";
    };

  public:
    Assets();

    const AssetPool<TextureIDKey, Texture> &textures() const
    {
        return m_textures;
    }
    const AssetPool<SpriteSheetIDKey, SpriteSheet> &spriteSheets() const
    {
        return m_spriteSheets;
    }
    const AssetPool<FontIDKey, Font> &fonts() const { return m_fonts; }
    const AssetPool<SoundIDKey, Sound> &sounds() const { return m_sounds; }

  private:
    void initTextures();
    void initSpriteSheets();
    void initSounds();
    void initFonts();

  private:
    AssetPool<TextureIDKey, Texture> m_textures;
    AssetPool<SpriteSheetIDKey, SpriteSheet> m_spriteSheets;
    AssetPool<FontIDKey, Font> m_fonts;
    AssetPool<SoundIDKey, Sound> m_sounds;
};
