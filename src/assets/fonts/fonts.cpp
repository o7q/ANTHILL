#include "fonts.hpp"

void initFonts(AssetPool<FontID, Font> &assets)
{
    std::unordered_map<FontID, FontLoadData> v;

    v[FontID::Default] = {"assets/fonts/default.png"};

    for (auto &[id, data] : v)
    {
        assets.add(id, std::make_unique<Font>(data.path));
    }
}
