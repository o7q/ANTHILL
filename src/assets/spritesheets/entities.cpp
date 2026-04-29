#include "spritesheets.hpp"

void initEntities(std::unordered_map<SpriteSheetIDKey, SpriteSheetLoadData> &v)
{
    const std::string base = "assets/spritesheets/entities/";

    v[SpriteSheetID::Entity_Wuskkogel] = {base + "wuskkogel/wuskkogel.png", {23, 22}};
}
