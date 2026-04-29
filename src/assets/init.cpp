#include "assets.hpp"
#include "assets/fonts/fonts.hpp"
#include "assets/sounds/sounds.hpp"
#include "assets/spritesheets/spritesheets.hpp"
#include "assets/textures/textures.hpp"

Assets::Assets()
{
    initTextures(m_textures);
    initSpriteSheets(m_spriteSheets);
    initSounds(m_sounds);
    initFonts(m_fonts);
}
