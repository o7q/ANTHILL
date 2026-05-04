#include "test_scene.hpp"

#include "backend/texture/texture.hpp"
#include "backend/viewport/render_command.hpp"

void TestScene::onStart() {}

void TestScene::onTick()
{
    std::vector<RenderCommand> renderCommands;

    Vec2i viewportMousePos =
        r_window.getViewport().windowToViewportPosition(r_window.getInput().getMousePosition());

    if (r_window.getInput().getInput(InputID::AltAction1)->isDown())
    {
        VerletBody body;
        body.setPosition(viewportMousePos.toFloat());
        m_bodies.push_back(body);

        if (m_bodies.size() >= 2)
        {
            int i1 = m_bodies.size() - 2;
            int i2 = m_bodies.size() - 1;

            VerletLink link(i1, i2);

            if (i1 == 0)
            {
                link.pinI1(true);
            }

            link.setDistance(1.0f);
            m_links.push_back(link);
        }
    }

    if (r_window.getInput().getInput(InputID::Shoot)->isDown())
    {
        VerletBody &body = m_bodies[m_bodies.size() - 1];

        Vec2f vel = (viewportMousePos.toFloat() - body.getPosition()).normalize() * 70.0f;

        body.addForce(vel);
    }

    for (size_t i = 0; i < m_bodies.size(); ++i)
    {
        if (i == 0)
        {
            continue;
        }
        // m_bodies[i].addForce({0, 1});
    }

    for (size_t i = 0; i < m_bodies.size(); ++i)
    {
        m_bodies[i].integrate(r_window.getTime().getInfo().dt);
    }

    for (int i = 0; i < 100; ++i)
    {
        for (VerletLink &link : m_links)
        {
            link.update(m_bodies[link.getI1()], m_bodies[link.getI2()]);
        }
    }

    for (VerletBody &body : m_bodies)
    {
        m_drawTex.setPixel(body.getPosition().toGrid().toUnsignedInt(), Color(255, 255, 255));
    }

    TextureRenderCommandData data;
    data.texture = &m_drawTex;
    data.origin  = {0, 0};
    renderCommands.push_back({0, data});

    r_window.getViewport().render(renderCommands);

    for (unsigned int y = 0; y < m_drawTex.getSize().y; ++y)
    {
        for (unsigned int x = 0; x < m_drawTex.getSize().x; ++x)
        {
            Color col = m_drawTex.getPixel({x, y});
            col.r *= 0.7;
            col.g *= 0.8;
            col.b *= 0.9;
            m_drawTex.setPixel({x, y}, col);
        }
    }
}
