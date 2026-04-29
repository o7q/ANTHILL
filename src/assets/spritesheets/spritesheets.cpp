#include "spritesheets.hpp"

void initSpriteSheets(AssetPool<SpriteSheetIDKey, SpriteSheet> &assets)
{
    std::unordered_map<SpriteSheetIDKey, SpriteSheetLoadData> v;

    initSumi(v);
    initEntities(v);
    initItems(v);

    for (auto &[id, data] : v)
    {
        assets.add(id, std::make_unique<SpriteSheet>(data.path, data.size));
    }
}
