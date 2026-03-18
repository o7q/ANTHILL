#pragma once

#include "assets.hpp"
#include "item/weapon/gun.hpp"

class Pistol : public Gun
{
  public:
    Pistol(const Assets &assets)
        : Gun("Pistol", *assets.textures().get("pistol"))
    {
    }

  protected:
    virtual void fire() override {}
};
