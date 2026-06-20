#pragma once

#include "px/utils/rectangle.hpp"
#include "px/renderer/render_command.hpp"
#include "ui/element.hpp"
#include <functional>

class UIButton : public UIElement
{
  public:
    virtual void update(const ElementUpdateContext &context) override
    {
        m_hovering = m_rect.pointInside(context.mousePos);
        m_clicked  = m_hovering && context.clicked;

        if (m_clicked && m_onClickFunction)
        {
            m_onClickFunction();
        }

        update_internal();
    }

    virtual void render(std::vector<RenderCommand> &commandsOut) override
    {
        RectangleRenderCommandData data;
        data.a     = m_rect.getA();
        data.b     = m_rect.getB();
        data.px::Color = m_hovering ? Color(255, 255, 0) : Color(0, 255, 0);
        data.fill  = true;

        commandsOut.push_back({10000, data});
    }

    void setOnClickFunction(std::function<void()> onClickFunction) { m_onClickFunction = onClickFunction; }

    void setRect(px::Rectangle_i rect) { m_rect = rect; }

  protected:
    virtual void update_internal() {}

  private:
    px::Rectangle_i m_rect;

    bool m_clicked  = false;
    bool m_hovering = false;

    std::function<void()> m_onClickFunction;
};
