#include "textures.hpp"

void initTextures(AssetPool<TextureID, Texture> &assets)
{
    std::unordered_map<TextureID, TextureLoadData> v;

    initBackgrounds(v);

    for (auto &[id, data] : v)
    {
        assets.add(id, std::make_unique<Texture>(data.path));
    }
}
