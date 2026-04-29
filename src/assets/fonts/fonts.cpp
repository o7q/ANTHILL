#include "fonts.hpp"

void initFonts(AssetPool<FontIDKey, Font> &assets)
{
    std::unordered_map<FontIDKey, FontLoadData> v;

    v[FontID::Default] = {"assets/fonts/default.png"};

    for (auto &[id, data] : v)
    {
        assets.add(id, std::make_unique<Font>(data.path));
    }
}
