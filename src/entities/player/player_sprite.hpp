#pragma once

#include "assets/assets.hpp"
#include "identifiers/assets/spritesheet.hpp"
#include "sprite/character_sprite.hpp"
#include "sprite/sprite_animator.hpp"
#include <optional>

enum class PlayerBodyPart
{
    Head,
    Torso,
    Legs
};

enum class PlayerAnimation
{
    Run,
    Idle
};

class PlayerSprite : public CharacterSprite<PlayerBodyPart, PlayerAnimation>
{
  public:
    PlayerSprite(const Assets &assets);

  private:
    void init_run(const Assets &assets);
    void init_idle(const Assets &assets);
};
