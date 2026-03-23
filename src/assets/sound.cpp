#include "assets.hpp"
#include <memory>

void Assets::initSounds()
{
    m_sounds.add(SoundID::Gunshot,
                 std::make_unique<Sound>("assets/gunshot.wav"));
    m_sounds.add(SoundID::BBW,
                 std::make_unique<Sound>("assets/ballad of bbws 2.wav"));
}
