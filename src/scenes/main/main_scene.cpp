#include "main_scene.hpp"

#include "px/canvas/canvas.hpp"
#include "px/canvas/draw_types.hpp"
#include "px/texture/texture.hpp"

void MainScene::onStart()
{
    m_world.getEntityHandler().addPlayer(std::make_unique<Player>(r_instance.input(), r_assets));
    m_world.getEntityHandler().getCurrentPlayer()->getBody().setPosition({-50, -20});
    // r_window.getSound().playSound(r_assets.sounds().get(SoundID::MusicAction), {0.5f});
}

void MainScene::onTick()
{
    if (r_instance.input().getInput("shoot").wasPressed())
    {
        m_renderTexture = px::Texture(m_renderTexture.getSize());
    }

    px::Canvas canvas(m_renderTexture);
    canvas.clear();

    std::vector<px::DrawCommand> renderCommands;

    m_camera.setViewSize(m_renderTexture.getSize());

    px::Vec2i viewportMousePos = r_instance.window().windowToRenderPosition(
        r_instance.input().getMousePosition(), m_renderTexture.getSize());
    px::Vec2f viewportMousePosCenterNormalized =
        (viewportMousePos - m_renderTexture.getSize().toInt() / 2).toFloat() /
        m_renderTexture.getSize().toFloat();

    px::Vec2i worldMousePos = m_camera.viewportToCamera(viewportMousePos);

    px::Vec2i updatePos;
    if (Player *player = m_world.getEntityHandler().getCurrentPlayer())
    {
        player->updateAimPosition(worldMousePos);
        updatePos = m_camera.getPosition();
    }

    if (r_instance.input().getInput("debug1").isDown())
    {
        Particle p;
        p.setColor({255, 251, 189, 255});
        p.setRestitution(0.1f);
        p.setMatterType(Particle::MatterType::Solid);
        p.setPhysicsType(Particle::PhysicsType::Sand);
        m_world.getParticleHandler().getEditor().setRadius(worldMousePos, p);
    }
    if (r_instance.input().getInput("debug2").isDown())
    {
        Particle p;
        p.setColor({0, 255, 255, 255});
        p.setRestitution(0.9f);
        p.setMatterType(Particle::MatterType::Solid);
        p.setPhysicsType(Particle::PhysicsType::Sand);
        m_world.getParticleHandler().getEditor().setRadius(worldMousePos, p);
    }
    if (r_instance.input().getInput("debug3").isDown())
    {
        Particle p;
        p.setColor({158, 249, 255, 200});
        p.setRestitution(0.4f);
        p.setMatterType(Particle::MatterType::Liquid);
        p.setPhysicsType(Particle::PhysicsType::Water);
        m_world.getParticleHandler().getEditor().setRadius(worldMousePos, p);
    }

    m_generator.generate(updatePos.toInt(), {10, 10});
    m_world.update(r_instance.time(), updatePos, m_events);

    if (Player *player = m_world.getEntityHandler().getCurrentPlayer())
    {
        m_camera.setGoal(player->getBody().getPosition() +
                         (viewportMousePosCenterNormalized * 60.0f).toGrid());
        m_camera.update(r_instance.time());
    }

    m_world.render(m_camera, r_assets, renderCommands);

    renderText(renderCommands);

    handle_events();
    canvas.drawCommandQueue(renderCommands);

    r_instance.window().render(m_renderTexture);
}
