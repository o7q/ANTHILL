#include "backend/font/font.hpp"
#include "assets.hpp"
#include <unordered_map>

void Assets::initFonts()
{
    std::unordered_map<FontIDKey, FontLoadData> fonts;

    fonts[FontID::Default] = {"assets/fonts/default.png"};

    for (auto &[id, data] : fonts)
    {
        m_fonts.add(id, std::make_unique<Font>(data.path));
    }
}
