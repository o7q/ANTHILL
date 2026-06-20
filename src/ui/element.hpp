#pragma once

#include "px/basic_types/vec.hpp"
#include "px/renderer/render_command.hpp"
#include <vector>

struct ElementUpdateContext
{
    px::Vec2i mousePos;
    bool clicked = false;
    bool down    = false;
};

class UIElement
{
  public:
    virtual void update(const ElementUpdateContext &context)     = 0;
    virtual void render(std::vector<RenderCommand> &commandsOut) = 0;
};
