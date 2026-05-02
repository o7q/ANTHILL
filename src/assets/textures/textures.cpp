#include "textures.hpp"

void initTextures(AssetPool<TextureIDKey, Texture> &assets)
{
    std::unordered_map<TextureIDKey, TextureLoadData> v;

    initBackgrounds(v);

    for (auto &[id, data] : v)
    {
        assets.add(id, std::make_unique<Texture>(data.path));
    }
}
