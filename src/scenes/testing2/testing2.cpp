#include "testing2.hpp"
#include "backend/viewport/viewport.hpp"
#include "math/index.hpp"
#include "math/perlin.hpp"
#include "math/random.hpp"

void TestScene2::onStart()
{
    m_colors.resize(r_viewport.getSize().x * r_viewport.getSize().y);
}

void TestScene2::onTick()
{
    if (r_input.getInput(InputID::Action1)->isDown())
    {
        Vec2i mousePos = r_viewport.windowToViewportPosition(
            r_window.getInputHandler().getMousePosition());

        for (unsigned int y = mousePos.y; y < mousePos.y + 30; ++y)
        {
            for (unsigned int x = mousePos.x; x < mousePos.x + 30; ++x)
            {
                float s = (Math::Perlin::sampleEx(x, y, 50, 10, 0) + 1) / 2.0f;

                unsigned int index =
                    Math::Index::index_2dto1d(x, y, r_viewport.getSize().x);
                Color color(s * 255, s * 255, s * 255);
                m_colors[index] = color;
            }
        }
    }

    for (unsigned int i = 0; i < m_colors.size(); ++i)
    {
        Vec2u index = Math::Index::index_1dTo2d(i, r_viewport.getSize().x);
        r_viewport.setPixel(index.x, index.y, m_colors[i]);
    }
}
