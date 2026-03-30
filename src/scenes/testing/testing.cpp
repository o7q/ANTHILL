#include "testing.hpp"
#include "entities/droid.hpp"
#include "identifiers/spritesheet.hpp"
#include "math/random.hpp"
#include "sprite/sprite_animator.hpp"

void TestScene::onStart()
{
    m_world.getEntityHandler().addPlayer(std::make_unique<Player>(
        m_world.getEntityHandler().getIDHandler().getNext(), r_input,
        r_assets));

    // for (int i = 0; i < 1; ++i)
    // {
    //     auto droid = std::make_unique<Droid>(
    //         m_world.getEntityHandler().getIDHandler().getNext(), r_assets);

    //     droid->getBody().setPosition({5 * i, 0});

    //     m_world.getEntityHandler().addEntity(std::move(droid));
    // }

    Particle stone;
    stone.setColor(Color(200, 205, 200));
    stone.setPhysicsType(Particle::PhysicsType::None);
    stone.setMatterType(Particle::MatterType::Solid);
    stone.getVerlet().setMass(200000000);
    stone.setImmovable(true);

    m_world.getParticleWorld().getEditor().draw({0, 300}, stone, 150);

    for (int i = 0; i < 1000; ++i)
    {
        int sign = Math::Random::weakRandInt(0, 2) == 0 ? -1 : 1;

        m_world.getParticleWorld().getEditor().draw(
            {sign * Math::Random::weakRandInt(50, 1000),
             Math::Random::weakRandInt(300, 400)},
            stone, 30);
    }

    Particle p;
    p.setImmovable(false);
    p.setPhysicsType(Particle::PhysicsType::Sand);
    p.setMatterType(Particle::MatterType::Solid);
    p.setDensity(1);
    p.setRestitution(0.8);
    p.getVerlet().setMass(1);

    m_world.getParticleWorld().getEditor().textureToParticles(
        *r_assets.textures().get(TextureID::Carter), Vec2i(100, 250), p);

    m_animator.add(
        SpriteAnimator(*r_assets.spriteSheets().get(SpriteSheetID::CatBoinga)),
        "boinga1");

    m_animator.switchAnimation("boinga1");
}

void TestScene::onTick()
{
    Vec2i viewportMousePos =
        r_viewport.windowToViewportPosition(r_input.getMousePosition());
    Vec2i worldMousePos =
        m_world.getCamera().viewportToWorld(viewportMousePos, r_viewport);

    if (r_window.getInputHandler().getInput(InputID::AltAction1)->isDown())
    {
        Particle stone;
        float mult = Math::Random::weakRandInt(80, 100) / 100.0f;
        stone.setColor(Color(200 * mult, 205 * mult, 200 * mult));
        stone.setPhysicsType(Particle::PhysicsType::None);
        stone.setMatterType(Particle::MatterType::Solid);
        stone.getVerlet().setMass(200000000);
        stone.setImmovable(true);

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
        sand.getVerlet().setMass(1);

        m_world.getParticleWorld().getEditor().draw(worldMousePos, sand, 4);
    }

    m_world.getEntityHandler().getCurrentPlayer()->updateAimPosition(
        worldMousePos);
    if (Player *player = m_world.getEntityHandler().getCurrentPlayer())
    {
        Vec2i playerPos = player->getBody().getPosition();
        m_world.getGenerator().generateInRadius(playerPos.toInt(), {20, 20});
        m_world.getCamera().setGoal(playerPos);
    }
    m_world.update(r_time.getDT());
    m_world.render(r_viewport);

    Texture fpsText =
        r_assets.fonts()
            .get(FontID::Test)
            ->generateStringTexture(std::to_string((int)r_time.getFPS()),
                                    Color(0, 255, 0), 5, 1, 8);
    r_viewport.drawTexture(fpsText, {10, 5});

    if (Player *player = m_world.getEntityHandler().getCurrentPlayer())
    {
        Vec2f playerPos = player->getBody().getPositionFloat();
        Texture posTest =
            r_assets.fonts()
                .get(FontID::Test)
                ->generateStringTexture(std::to_string((int)playerPos.x) + " " +
                                            std::to_string((int)playerPos.y),
                                        Color(255, 255, 0), 5, 1, 8);
        r_viewport.drawTexture(posTest, {50, 5});
    }

    if (SpriteAnimator *a = m_animator.getCurrentAnimator())
    {
        a->setFPS(20);
        a->update(r_time.getDT());
        for (int y = 0; y < 10; ++y)
        {
            for (int x = 0; x < 10; ++x)
            {
                r_viewport.drawTexture(*a->getCurrentFrame(),
                                       m_world.getCamera().worldToViewport(
                                           {x * 20, y * 20}, r_viewport));
            }
        }
    }
}
