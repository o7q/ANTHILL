#pragma once

#include "entities/projectile/projectile.hpp"
#include "item/weapon/gun.hpp"
#include <memory>
class Pistol : public Gun
{
  public:
  protected:
    virtual void fire() override {
    }
};
