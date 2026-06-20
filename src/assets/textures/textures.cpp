#include "textures.hpp"

void initTextures(px::AssetPool<TextureID, px::Texture> &assets)
{
    std::unordered_map<TextureID, TextureLoadData> v;

    initBackgrounds(v);

    for (auto &[id, data] : v)
    {
        assets.add(id, std::make_unique<px::Texture>(data.path));
    }
}
