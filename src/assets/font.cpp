#include "assets.hpp"

void Assets::initFonts()
{
    m_fonts.add(FontID::Default,
                std::make_unique<Font>("assets/fonts/default.png"));
}
