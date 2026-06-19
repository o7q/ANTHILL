#pragma once

#include "px/asset_pool/asset_pool.hpp"
#include "px/font/font.hpp"
#include "px/sound/sound.hpp"
#include "px/sprite_sheet/sprite_sheet.hpp"
#include "px/texture/texture.hpp"
#include "identifiers/fonts.hpp"
#include "identifiers/rooms.hpp"
#include "identifiers/sounds.hpp"
#include "identifiers/spritesheet.hpp"
#include "identifiers/textures.hpp"
#include "room/room.hpp"

class Assets
{
  public:
    Assets();

    const AssetPool<TextureID, Texture> &textures() const { return m_textures; }
    const AssetPool<SpriteSheetID, SpriteSheet> &spriteSheets() const { return m_spriteSheets; }
    const AssetPool<FontID, Font> &fonts() const { return m_fonts; }
    const AssetPool<SoundID, Sound> &sounds() const { return m_sounds; }
    const AssetPool<RoomID, Room> &rooms() const { return m_rooms; }

  private:
    AssetPool<TextureID, Texture> m_textures;
    AssetPool<SpriteSheetID, SpriteSheet> m_spriteSheets;
    AssetPool<FontID, Font> m_fonts;
    AssetPool<SoundID, Sound> m_sounds;
    AssetPool<RoomID, Room> m_rooms;
};
