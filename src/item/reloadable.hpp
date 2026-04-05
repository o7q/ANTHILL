#pragma once

#include "identifiers/assets/sounds.hpp"
class IReloadable
{
  public:
    virtual void reload() = 0;
    virtual const SoundIDKey getReloadSound() const = 0;
};
