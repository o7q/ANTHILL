#include "assets.hpp"
#include <memory>

void Assets::initSounds()
{
    m_sounds.add(SoundID::Gunshot,
                 std::make_unique<Sound>("assets/sounds/gunshot.wav"));
    m_sounds.add(SoundID::BBW,
                 std::make_unique<Sound>("assets/sounds/ballad of bbws 2.wav"));
    m_sounds.add(SoundID::Bite,
                 std::make_unique<Sound>("assets/sounds/bite.wav"));
}
