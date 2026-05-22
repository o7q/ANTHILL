#pragma once

#include "core/math/geometry/vec.hpp"
#include "core/viewport/render_command.hpp"
#include <vector>

struct ElementUpdateContext
{
    Vec2i mousePos;
    bool clicked = false;
    bool down    = false;
};

class UIElement
{
  public:
    virtual void update(const ElementUpdateContext &context)     = 0;
    virtual void render(std::vector<RenderCommand> &commandsOut) = 0;
};
