#include "verlet_test_scene.hpp"

#include "px/texture/texture.hpp"
#include "px/window/draw_types.hpp"

void VerletTestScene::onStart() {}

void VerletTestScene::onTick()
{
    std::vector<px::DrawCommand> renderCommands;

    px::Vec2i viewportMousePos =
        r_instance.window().windowToViewportPosition(r_instance.input().getMousePosition());

    if (r_instance.input().getInput("jump").isDown())
    {
        px::VerletBody body;
        body.setPosition(viewportMousePos.toFloat());
        m_bodies.push_back(body);

        if (m_bodies.size() >= 2)
        {
            int i1 = m_bodies.size() - 2;
            int i2 = m_bodies.size() - 1;

            px::VerletLink link(i1, i2);

            if (i1 == 0)
            {
                link.pinVerlet1(true);
            }

            link.setDistance(1.0f);
            m_links.push_back(link);
        }
    }

    if (r_instance.input().getInput("shoot").isDown())
    {
        px::VerletBody &body = m_bodies[m_bodies.size() - 1];

        px::Vec2f vel = (viewportMousePos.toFloat() - body.getPosition()).normalize() * 70.0f;

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
        m_bodies[i].integrate(r_instance.time().getDeltaTime());
    }

    for (int i = 0; i < 100; ++i)
    {
        for (px::VerletLink &link : m_links)
        {
            link.update(m_bodies[link.getVerletID1()], m_bodies[link.getVerletID2()]);
        }
    }

    for (px::VerletBody &body : m_bodies)
    {
        m_drawTex.setPixel(body.getPosition().toGrid().toUnsignedInt(), px::Color(255, 255, 255));
    }

    px::TextureDrawConfig data;
    data.texture = &m_drawTex;
    data.origin  = {0, 0};
    renderCommands.push_back({0, data});

    r_instance.window().drawCommandQueue(renderCommands);

    for (unsigned int y = 0; y < m_drawTex.getSize().y; ++y)
    {
        for (unsigned int x = 0; x < m_drawTex.getSize().x; ++x)
        {
            px::Color col = m_drawTex.getPixel({x, y});
            col.r *= 0.7;
            col.g *= 0.8;
            col.b *= 0.9;
            m_drawTex.setPixel({x, y}, col);
        }
    }
}
