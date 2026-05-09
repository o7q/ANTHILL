#include "spritesheets.hpp"

void initSpriteSheets(AssetPool<SpriteSheetID, SpriteSheet> &assets)
{
    std::unordered_map<SpriteSheetID, SpriteSheetLoadData> v;

    initSumi(v);
    initEntities(v);
    initItems(v);

    for (auto &[id, data] : v)
    {
        assets.add(id, std::make_unique<SpriteSheet>(data.path, data.size));
    }
}
