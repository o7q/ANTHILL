#include "spritesheets.hpp"

void initSpriteSheets(px::AssetPool<SpriteSheetID, px::SpriteSheet> &assets)
{
    std::unordered_map<SpriteSheetID, SpriteSheetLoadData> v;

    initSumi(v);
    initEntities(v);

    for (auto &[id, data] : v)
    {
        assets.add(id, std::make_unique<px::SpriteSheet>(data.path, data.size));
    }
}
