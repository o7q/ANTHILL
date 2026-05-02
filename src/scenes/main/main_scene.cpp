#include "main_scene.hpp"

#include "backend/viewport/render_command.hpp"
#include "math/random.hpp"
#include <memory>

void MainScene::onStart()
{
    m_world.getEntityHandler().addPlayer(std::make_unique<Player>(
        m_world.getEntityHandler().getIDHandler().getNext(), r_window.getInput(), r_assets));

    m_world.getEntityHandler().getCurrentPlayer()->getBody().setPosition({0, -200});

    m_slowTimer.setDurationInSeconds(2);
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
        stone.setMass(200000000);

        m_world.getParticleHandler().getEditor().draw(worldMousePos, stone, 20);
    }
    if (r_window.getInput().getInput(InputID::AltAction2)->isDown())
    {
        Particle air;

        m_world.getParticleHandler().getEditor().draw(worldMousePos, air, 10);
    }
    if (r_window.getInput().getInput(InputID::AltAction3)->isDown())
    {
        Particle sandstone;
        sandstone.setColor(Color(255, 255, 0));
        sandstone.setPhysicsType(Particle::PhysicsType::Sandstone);
        sandstone.setMatterType(Particle::MatterType::Solid);

        m_world.getParticleHandler().getEditor().draw(worldMousePos, sandstone, 5);
    }
    if (r_window.getInput().getInput(InputID::AltAction4)->isDown())
    {
        m_slowTimer.restart();
    }
    if (r_window.getInput().getInput(InputID::AltAction5)->isDown())
    {
        requestSceneChange(SceneID::Test);
    }

    m_slowTimer.update(r_window.getTime().getInfo().dt_raw);

    if (m_slowTimer.active())
    {
        r_window.getTime().setSpeedMultiplier(m_slowTimer.getProgress());
    }
    else
    {
        r_window.getTime().setSpeedMultiplier(1);
    }

    Player *player = m_world.getEntityHandler().getCurrentPlayer();
    Vec2i updatePos;
    if (player)
    {
        player->updateAimPosition(worldMousePos);
        updatePos = m_camera.getPosition();
    }

    m_generator.generate(updatePos.toInt(), {10, 10});
    m_world.update(r_window.getTime().getInfo(), updatePos, m_backendEvents);

    if (player)
    {
        player->updateAimPosition(worldMousePos);
        updatePos = player->getBody().getPosition();
    }
    m_camera.setGoal(updatePos + (viewportMousePosCenterNormalized * 60.0f).toInt());
    m_camera.update(r_window.getTime().getInfo());

    m_world.render(m_camera, r_assets, renderCommands);

    renderText(renderCommands);
    r_window.getViewport().render(renderCommands);
}
