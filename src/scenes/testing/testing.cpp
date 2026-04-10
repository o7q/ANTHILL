#include "testing.hpp"
#include "backend/viewport/render_command.hpp"
#include "entities/wuskkogel/wuskkogel.hpp"
#include <memory>

void TestScene::onStart()
{
    m_world.getEntityHandler().addPlayer(std::make_unique<Player>(
        m_world.getEntityHandler().getIDHandler().getNext(), r_input,
        r_assets));

    m_world.getEntityHandler().getCurrentPlayer()->getBody().setPosition(
        {0, -200});

    for (int i = 0; i < 1; ++i)
    {
        auto wuskkogel = std::make_unique<Wuskkogel>(
            m_world.getEntityHandler().getIDHandler().getNext(), r_assets);
        wuskkogel->getBody().setPosition({i * 10, -20});
        m_world.getEntityHandler().addEntity(std::move(wuskkogel));
    }
}

void TestScene::onTick()
{
    std::vector<RenderCommand> renderCommands;

    m_camera.setViewSize(r_viewport.getSize());

    Vec2i viewportMousePos =
        r_viewport.windowToViewportPosition(r_input.getMousePosition());
    Vec2i worldMousePos = m_camera.viewportToCamera(viewportMousePos);

    if (r_window.getInputHandler().getInput(InputID::AltAction1)->isDown())
    {

        Particle stone;
        float mult = Math::Random::weakRandInt(80, 100) / 100.0f;
        stone.setColor(Color(200 * mult, 205 * mult, 200 * mult));
        stone.setPhysicsType(Particle::PhysicsType::None);
        stone.setMatterType(Particle::MatterType::Solid);
        stone.setMass(200000000);

        m_world.getParticleWorld().getEditor().draw(worldMousePos, stone, 20);
    }
    if (r_window.getInputHandler().getInput(InputID::AltAction2)->isDown())
    {
        Particle air;

        m_world.getParticleWorld().getEditor().draw(worldMousePos, air, 10);
    }
    if (r_window.getInputHandler().getInput(InputID::AltAction3)->isDown())
    {
        Particle sand;
        float mult = Math::Random::weakRandInt(80, 100) / 100.0f;
        sand.setColor(Color(255 * mult, 235 * mult, 161 * mult));
        sand.setPhysicsType(Particle::PhysicsType::Sand);
        sand.setMatterType(Particle::MatterType::Solid);
        sand.setRestitution(0.1f);

        m_world.getParticleWorld().getEditor().draw(worldMousePos, sand, 4);
    }

    Player *player = m_world.getEntityHandler().getCurrentPlayer();
    Vec2i updatePos;
    Texture healthText;
    if (player)
    {
        player->updateAimPosition(worldMousePos);
        updatePos = player->getBody().getPosition();

        healthText = r_assets.fonts()
                         .get(FontID::Default)
                         ->generateStringTexture(
                             std::to_string((int)player->getHealth()),
                             Color(255, 100, 100), 5, 1, 8);

        TextureRenderCommandData healthRenderData;
        healthRenderData.texture = &healthText;
        healthRenderData.position = {70, 5};
        renderCommands.push_back({1000, healthRenderData});
    }

    m_camera.setGoal(updatePos);
    m_camera.update(r_time.getDT());
    m_world.getGenerator().generateInRadius(updatePos.toInt(), {20, 20});
    m_world.update(r_time.getDT(), updatePos, {300, 300}, m_backendEvents);
    m_world.render(m_camera, r_assets, renderCommands);

    Texture fpsText =
        r_assets.fonts()
            .get(FontID::Default)
            ->generateStringTexture(std::to_string((int)r_time.getFPS()),
                                    Color(0, 255, 0), 5, 1, 8);

    TextureRenderCommandData fpsRenderData;
    fpsRenderData.texture = &fpsText;
    fpsRenderData.position = {10, 5};
    renderCommands.push_back({1000, fpsRenderData});

    Texture entitiesText =
        r_assets.fonts()
            .get(FontID::Default)
            ->generateStringTexture(
                std::to_string(m_world.getEntityHandler().getEntityCount()),
                Color(255, 100, 255), 5, 1, 8);

    TextureRenderCommandData entitiesRenderData;
    entitiesRenderData.texture = &entitiesText;
    entitiesRenderData.position = {40, 5};
    renderCommands.push_back({1000, entitiesRenderData});

    r_viewport.render(renderCommands);
}
