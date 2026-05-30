#include "main_scene.hpp"

#include "core/math/random.hpp"
#include "core/time/time_handler.hpp"
#include "core/viewport/render_command.hpp"
#include "entities/wuskkogel/wuskkogel.hpp"

void MainScene::onStart()
{
    m_world.getEntityHandler().addPlayer(std::make_unique<Player>(r_window.getInput(), r_assets));
    m_world.getEntityHandler().getCurrentPlayer()->getBody().setPosition({0, -200});
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
        stone.setRestitution(1.0f);

        m_world.getParticleHandler().getEditor().setRadius(worldMousePos, stone, 20);
    }
    if (r_window.getInput().getInput(InputID::AltAction2)->isDown())
    {
        Particle air;

        m_world.getParticleHandler().getEditor().setRadius(worldMousePos, air, 10);
    }
    if (r_window.getInput().getInput(InputID::AltAction3)->isDown())
    {
        Particle sand;
        float mult = Math::Random::unseededRandomInt(80, 100) / 100.0f;
        sand.setColor(Color(255 * mult, 226 * mult, 145 * mult));
        sand.setPhysicsType(Particle::PhysicsType::Sand);
        sand.setMatterType(Particle::MatterType::Solid);
        sand.setMass(1);

        m_world.getParticleHandler().getEditor().setRadius(worldMousePos, sand, 5);
    }
    if (r_window.getInput().getInput(InputID::AltAction4)->isDown())
    {
        Particle bouncy;
        float mult = Math::Random::unseededRandomInt(80, 100) / 100.0f;
        bouncy.setColor(Color(92 * mult, 255, 225));
        bouncy.setPhysicsType(Particle::PhysicsType::Sand);
        bouncy.setMatterType(Particle::MatterType::Solid);
        bouncy.setMass(1);
        bouncy.setRestitution(0.9f);

        m_world.getParticleHandler().getEditor().setRadius(worldMousePos, bouncy, 5);
    }
    if (r_window.getInput().getInput(InputID::AltAction5)->isDown())
    {
        m_world.getParticleHandler().getDynamics().applyForce(worldMousePos, 200, 10);
        // auto entity = std::make_unique<Wuskkogel>(r_assets);
        // entity->getBody().setPosition(worldMousePos);
        // m_world.getEntityHandler().addEntity(std::move(entity));
    }

    Vec2i updatePos;
    if (Player *player = m_world.getEntityHandler().getCurrentPlayer())
    {
        player->updateAimPosition(worldMousePos);
        updatePos = m_camera.getPosition();
    }

    m_generator.generate(updatePos.toInt(), {10, 10});
    m_world.update(r_window.getTime().getInfo(), {updatePos, {280 + 50, 210 + 50}}, m_events);

    if (Player *player = m_world.getEntityHandler().getCurrentPlayer())
    {
        m_camera.setGoal(player->getBody().getPosition() +
                         (viewportMousePosCenterNormalized * 60.0f).toGrid());
        m_camera.update(r_window.getTime().getInfo());
    }

    m_world.render(m_camera, r_assets, renderCommands);

    renderText(renderCommands);

    r_window.getViewport().render(renderCommands);
}
