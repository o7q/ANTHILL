#pragma once

#include "entity/interfaces/directional.hpp"
#include "math/vec.hpp"

class IHead : public IDirectional
{
  public:
    Vec2i getHeadPosition() const { return m_headPosition; }

  protected:
    Vec2i m_headPosition;
};
