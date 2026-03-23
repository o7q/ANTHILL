#include "assets.hpp"

void Assets::initFonts()
{
    m_fonts.add(FontID::Test,
                std::make_unique<Font>("assets/images/fonts/test.png"));
}
