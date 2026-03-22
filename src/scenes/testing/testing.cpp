#include "testing.hpp"
#include "entities/test.hpp"
#include "math/random.hpp"

void TestScene::onStart()
{
    m_world.getEntityHandler().addPlayer(std::make_unique<Player>(
        m_world.getEntityHandler().getIDHandler().getNext(), r_input,
        r_assets));

    for (int i = 0; i < 1; ++i)
    {
        std::unique_ptr<TestEntity> test = std::make_unique<TestEntity>(
            m_world.getEntityHandler().getIDHandler().getNext());

        test->getBody().setPosition(5 * i, 0);

        m_world.getEntityHandler().addEntity(std::move(test));
    }

    Particle stone;
    stone.setColor(Color(200, 205, 200));
    stone.setPhysicsType(Particle::PhysicsType::None);
    stone.setMatterType(Particle::MatterType::Solid);
    stone.getVerlet().setMass(200000000);
    stone.setImmovable(true);

    m_world.getParticleHandler().draw(0, 300, stone, 150);

    for (int i = 0; i < 1000; ++i)
    {
        int sign = Math::Random::weakRandInt(0, 2) == 0 ? -1 : 1;

        m_world.getParticleHandler().draw(
            sign * Math::Random::weakRandInt(50, 1000),
            Math::Random::weakRandInt(300, 400), stone, 30);
    }

    Particle p;
    p.setImmovable(false);
    p.setPhysicsType(Particle::PhysicsType::Sand);
    p.setMatterType(Particle::MatterType::Solid);
    p.setDensity(1);
    p.setRestitution(0.8);
    p.getVerlet().setMass(1);

    m_world.getParticleHandler().textureToParticles(
        *r_assets.textures().get(TextureID::Noodle), Vec2<int>(100, 250), p);
}

void TestScene::onTick()
{
    Vec2<float> mousePos = r_input.getMousePosition();
    Vec2<int> viewportMousePos = r_viewport.windowToViewportPosition(mousePos);

    Vec2<int> worldPos = m_world.getCamera().viewportToWorld(
        viewportMousePos.x, viewportMousePos.y, r_viewport);

    if (r_window.getInputHandler()
            .getInput(InputID::SecondaryAction1)
            ->isDown())
    {

        Particle stone;
        float mult = Math::Random::weakRandInt(80, 100) / 100.0f;
        stone.setColor(Color(200 * mult, 205 * mult, 200 * mult));
        stone.setPhysicsType(Particle::PhysicsType::None);
        stone.setMatterType(Particle::MatterType::Solid);
        stone.getVerlet().setMass(200000000);
        stone.setImmovable(true);

        m_world.getParticleHandler().draw(worldPos.x, worldPos.y, stone, 20);
    }
    if (r_window.getInputHandler()
            .getInput(InputID::SecondaryAction2)
            ->isDown())
    {
        Particle air;

        m_world.getParticleHandler().draw(worldPos.x, worldPos.y, air, 10);
    }
    if (r_window.getInputHandler()
            .getInput(InputID::SecondaryAction3)
            ->isDown())
    {
        Particle sand;
        float mult = Math::Random::weakRandInt(80, 100) / 100.0f;
        sand.setColor(Color(255 * mult, 235 * mult, 161 * mult));
        sand.setPhysicsType(Particle::PhysicsType::Sand);
        sand.setMatterType(Particle::MatterType::Solid);
        sand.setRestitution(0.1f);
        sand.getVerlet().setMass(1);

        m_world.getParticleHandler().draw(worldPos.x, worldPos.y, sand, 4);
    }

    if (r_window.getInputHandler().getInput(InputID::Action1)->isDown())
    {
        // m_world.getParticleHandler().getDynamics().applyForce(
        //     worldPos.x, worldPos.y, 100, r_time.getDT());
    }

    if (r_window.getInputHandler()
            .getInput(InputID::SecondaryAction5)
            ->wasPressed())
    {
        loadScene(SceneID::Testing);
    }

    m_world.getEntityHandler().getCurrentPlayer()->updateAimPosition(worldPos);
    m_world.update(r_time.getDT());
    if (Player *player = m_world.getEntityHandler().getCurrentPlayer())
    {
        m_world.getCamera().setGoal(player->getBody().getPosition().x,
                                    player->getBody().getPosition().y);

        m_world.getCamera().update(r_time.getDT());
    }

    // std::cout << static_cast<int>(r_time.getFPS()) << std::endl;

    float angle = (viewportMousePos.x / (float)r_viewport.getSize().x) * 360;

    r_viewport.drawTextureRotated(
        *r_assets.textures().get(TextureID::Pistol),
        m_world.getCamera().worldToViewport(0, 0, r_viewport),
        Math::Angle::degreesToRadians(angle));

    GridRectangle rect;
    rect.setPosition(viewportMousePos.x, viewportMousePos.y);
    rect.setSize(30, 30);

    m_world.render(r_viewport);
}