#pragma once

#include "backend/assets/asset_store.hpp"
#include "backend/texture/texture.hpp"
#include "identifiers.hpp"

class Assets
{
  public:
    Assets()
    {
        m_textures.add(TextureID::Noodle,
                       std::make_unique<Texture>("noodle.png"));
        m_textures.add(TextureID::Pistol,
                       std::make_unique<Texture>("pistol.png"));
        m_textures.add(TextureID::PistolSmall,
                       std::make_unique<Texture>("pistol_small.png"));
        m_textures.add(TextureID::Character,
                       std::make_unique<Texture>("character.png"));
    }

    const AssetStore<TextureIDKey, Texture> &textures() const
    {
        return m_textures;
    }

  private:
    AssetStore<TextureIDKey, Texture> m_textures;
};
