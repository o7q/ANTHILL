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
    }

    const AssetStore<TextureIDKey, Texture> &textures() const
    {
        return m_textures;
    }

  private:
    AssetStore<TextureIDKey, Texture> m_textures;
};
