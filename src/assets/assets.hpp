#pragma once

#include "identifiers/fonts.hpp"
#include "identifiers/rooms.hpp"
#include "identifiers/sounds.hpp"
#include "identifiers/spritesheet.hpp"
#include "identifiers/textures.hpp"
#include "px/asset_pool/asset_pool.hpp"
#include "px/font/font.hpp"
#include "px/sound/sound.hpp"
#include "px/sprite_sheet/sprite_sheet.hpp"
#include "px/texture/texture.hpp"
#include "room/room.hpp"

class Assets
{
  public:
    Assets();

    const px::AssetPool<TextureID, px::Texture> &textures() const { return m_textures; }
    const px::AssetPool<SpriteSheetID, px::SpriteSheet> &spriteSheets() const { return m_spriteSheets; }
    const px::AssetPool<FontID, px::Font> &fonts() const { return m_fonts; }
    const px::AssetPool<SoundID, px::Sound> &sounds() const { return m_sounds; }
    const px::AssetPool<RoomID, Room> &rooms() const { return m_rooms; }

  private:
    px::AssetPool<TextureID, px::Texture> m_textures;
    px::AssetPool<SpriteSheetID, px::SpriteSheet> m_spriteSheets;
    px::AssetPool<FontID, px::Font> m_fonts;
    px::AssetPool<SoundID, px::Sound> m_sounds;
    px::AssetPool<RoomID, Room> m_rooms;
};
