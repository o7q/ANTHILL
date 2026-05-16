#pragma once

#include "core/viewport/render_command.hpp"
#include "ui/element.hpp"
#include <memory>
#include <vector>

class UI
{
  public:
    void update(const ElementUpdateContext &context)
    {
        for (auto &element : m_elements)
        {
            element->update(context);
        }
    }
    void render(std::vector<RenderCommand> &commandsOut)
    {
        for (auto &element : m_elements)
        {
            element->render(commandsOut);
        }
    }

  private:
    std::vector<std::unique_ptr<UIElement>> m_elements;
};
