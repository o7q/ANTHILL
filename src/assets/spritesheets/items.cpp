#include "spritesheets.hpp"

void initItems(std::unordered_map<SpriteSheetID, SpriteSheetLoadData> &v)
{
    const std::string base = "assets/spritesheets/items/";

    v[SpriteSheetID::Item_Shotgun] = {base + "shotgun/shotgun.png", {22, 12}};
}
