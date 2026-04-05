#pragma once

#include "backend/texture/texture.hpp"

class IRenderable
{
  public:
    virtual const Texture *getTexture() const = 0;
};
