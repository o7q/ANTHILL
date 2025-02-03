#include "game.hpp"

#include <iostream>
#include <cmath>
#include <SDL3_ttf/SDL_ttf.h>

#include "texture/texture.hpp"

#include "world/world.hpp"

#include "math/random.hpp"

#include "entity/entity.hpp"

Game::Game() : window("ANTHILL", 512, 512, 256)
{
    World world(window.getSDLRenderer(), 256, 256);
    Camera camera;
    camera.setPosition(Vec2<float>(-world.getSize().x / 2.0f, -world.getSize().y / 2.0f));

    window.time().setTargetFramerate(60);

    Random::seed();

    Entity entity(20, 30);

    Particle::Preset preset = Particle::Preset::Sand;
    while (window.isOpen())
    {
        window.time().frameStart();

        window.clear();
        window.update();

        if (window.input().isDown(Input::Up))
        {
            entity.move(Vec2<float>(0, -2));
            // camera.move(0, -1);
        }
        if (window.input().isDown(Input::Down))
        {
            entity.move(Vec2<float>(0, 2));
            // camera.move(0, 1);
        }
        if (window.input().isDown(Input::Left))
        {
            entity.move(Vec2<float>(-2, 0));
            // camera.move(-1, 0);
        }
        if (window.input().isDown(Input::Right))
        {
            entity.move(Vec2<float>(2, 0));
            // camera.move(1, 0);
        }

        if (window.input().wasPressed(Input::Debug1))
        {
            preset = Particle::Preset::Stone;
        }
        if (window.input().wasPressed(Input::Debug2))
        {
            preset = Particle::Preset::Sand;
        }
        if (window.input().wasPressed(Input::Debug3))
        {
            preset = Particle::Preset::Water;
        }
        if (window.input().wasPressed(Input::Debug4))
        {
            preset = Particle::Preset::Blood;
        }
        if (window.input().wasPressed(Input::Debug5))
        {
            preset = Particle::Preset::Steam;
        }

        Vec2<int> mousePos = window.input().getMousePos();
        if (window.input().isDown(Input::Action1))
        {
            Vec2<int> worldSize = world.getSize();

            Vec2<float> drawPos = camera.transformPoint(mousePos.x + worldSize.x / 2, mousePos.y + worldSize.y / 2);
            world.drawParticles(drawPos.x, drawPos.y, 5, preset);
            // world.setParticle(drawPos.x, drawPos.y, Particle(preset));
        }

        world.update();

        const std::vector<Segment> worldCollision = world.getWorldCollision();
        window.renderTexture(world.getWorldTexture(), &camera);

        // for (const Segment &seg : worldCollision)
        // {
        //     // window.debug_renderSegment(seg, 255, 50, 100, 255, &camera);

        //     Vec2<float> midpoint = Vec2<float>(
        //         (seg.a.x + seg.b.x) / 2.0f,
        //         (seg.a.y + seg.b.y) / 2.0f);

        //     SDL_SetRenderDrawColor(window.getSDLRenderer(), 255, 50, 100, 255);
        //     SDL_RenderPoint(window.getSDLRenderer(), midpoint.x - camera.getPosition().x, midpoint.y - camera.getPosition().y);
        //     SDL_SetRenderDrawColor(window.getSDLRenderer(), 0, 0, 0, 0);
        // }

        entity.update();
        entity.resolveWorldCollision(worldCollision);

        window.renderText(std::to_string((int)window.time().getFramerate()), Vec2<int>(1, window.getScale() - 10), Color(0, 255, 0, 255));
        window.renderText(std::to_string(window.time().getDeltaTime()), Vec2<int>(30, window.getScale() - 10), Color(255, 255, 0, 255));

        window.debug_renderBoundingBox(entity.getBoundingBox(), 0, 255, 100, 255, &camera);

        window.display();

        window.time().frameEnd();
        window.time().delay();
    }
}