#include "fonts.hpp"

void initFonts(px::AssetPool<FontID, px::Font> &assets)
{
    std::unordered_map<FontID, FontLoadData> v;

    v[FontID::Default] = {"assets/fonts/default.png"};

    for (auto &[id, data] : v)
    {
        assets.add(id, std::make_unique<px::Font>(data.path));
    }
}
