#include "main_scene.hpp"

#include "core/data_structures/node_graph.hpp"
#include "core/math/geometry/rectangle.hpp"
#include "core/math/line.hpp"
#include "core/math/random.hpp"
#include "core/time/time_handler.hpp"
#include "core/viewport/render_command.hpp"
#include "entities/player_point/player_point.hpp"
#include <iostream>

void MainScene::onStart()
{
    m_world.getEntityHandler().addPlayer(std::make_unique<Player>(r_window.getInput(), r_assets));
    m_world.getEntityHandler().getCurrentPlayer()->getBody().setPosition({0, -200});

    NodeGraph<Vec2i> graph = m_dungeonGenerator.generate();

    for (int y = m_dungeonGenerator.getBounds().getA().y; y < m_dungeonGenerator.getBounds().getB().y; ++y)
    {
        for (int x = m_dungeonGenerator.getBounds().getA().x; x < m_dungeonGenerator.getBounds().getB().x;
             ++x)
        {
            Particle p;
            p.setMatterType(Particle::MatterType::Solid);
            p.setPhysicsType(Particle::PhysicsType::None);
            p.setColor(Color(200));
            p.setMass(10000000);
            p.setRestitution(1);

            m_world.getParticleHandler().getEditor().set({x, y}, p);
        }
    }

    for (auto &[index, node] : graph.getNodes())
    {
        Rectangle_i rect(index, node.value);

        Vec2i a = rect.getA();
        Vec2i b = rect.getB();

        for (int y = a.y; y < b.y; ++y)
        {
            for (int x = a.x; x < b.x; ++x)
            {
                Particle p;
                m_world.getParticleHandler().getEditor().set({x, y}, p);
            }
        }
    }

    for (auto &[index, node] : graph.getNodes())
    {
        for (Vec2i neighbor : node.connections)
        {
            Math::Line::bresenhamLine(index, neighbor,
                                      [&](Vec2i pos)
                                      {
                                          m_world.getParticleHandler().getEditor().draw(pos, Particle(), 20);
                                          return false;
                                      });
        }
    }
}

void MainScene::onTick()
{
    std::vector<RenderCommand> renderCommands;

    m_camera.setViewSize(r_window.getViewport().getSize());

    Vec2i viewportMousePos =
        r_window.getViewport().windowToViewportPosition(r_window.getInput().getMousePosition());
    Vec2f viewportMousePosCenterNormalized =
        (viewportMousePos - r_window.getViewport().getSize().toInt() / 2).toFloat() /
        r_window.getViewport().getSize().toFloat();

    Vec2i worldMousePos = m_camera.viewportToCamera(viewportMousePos);

    if (r_window.getInput().getInput(InputID::AltAction1)->isDown())
    {
        Particle stone;
        float mult = Math::Random::unseededRandomInt(80, 100) / 100.0f;
        stone.setColor(Color(200 * mult, 205 * mult, 200 * mult));
        stone.setPhysicsType(Particle::PhysicsType::None);
        stone.setMatterType(Particle::MatterType::Solid);
        stone.setMass(200000000.0f);
        stone.setRestitution(1.0f);

        m_world.getParticleHandler().getEditor().draw(worldMousePos, stone, 20);
    }
    if (r_window.getInput().getInput(InputID::AltAction2)->isDown())
    {
        Particle air;

        m_world.getParticleHandler().getEditor().draw(worldMousePos, air, 10);
    }
    if (r_window.getInput().getInput(InputID::AltAction3)->isDown())
    {
        Particle sand;
        float mult = Math::Random::unseededRandomInt(40, 100) / 100.0f;
        sand.setColor(Color(43, 255, 202 * mult));
        sand.setPhysicsType(Particle::PhysicsType::Sand);
        sand.setMatterType(Particle::MatterType::Solid);
        sand.setMass(1.0f);
        sand.setRestitution(0.95f);

        m_world.getParticleHandler().getEditor().draw(worldMousePos, sand, 1);
    }
    if (r_window.getInput().getInput(InputID::AltAction4)->isDown())
    {
        auto entity = std::make_unique<PlayerPoint>(worldMousePos);
        entity->getBody().setPosition(worldMousePos);
        m_world.getEntityHandler().addEntity(std::move(entity));
    }

    Player *player = m_world.getEntityHandler().getCurrentPlayer();
    Vec2i updatePos;
    if (player)
    {
        player->updateAimPosition(worldMousePos);
        updatePos = m_camera.getPosition();
    }

    m_world.update(r_window.getTime().getInfo(), updatePos, m_events);

    if (player)
    {
        player->updateAimPosition(worldMousePos);
        updatePos = player->getBody().getPosition();
    }
    m_camera.setGoal(updatePos + (viewportMousePosCenterNormalized * 60.0f).toGrid());
    m_camera.update(r_window.getTime().getInfo());

    m_world.render(m_camera, r_assets, renderCommands);

    renderText(renderCommands);

    r_window.getViewport().render(renderCommands);
}
