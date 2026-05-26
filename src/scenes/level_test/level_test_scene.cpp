#include "level_test_scene.hpp"

#include "core/math/geometry/rectangle.hpp"
#include "core/math/random.hpp"
#include "core/viewport/render_command.hpp"
#include "level_generator/level_generator.hpp"
#include <vector>

void LevelTestScene::onStart() {}

void LevelTestScene::onTick()
{
    std::vector<RenderCommand> renderCommands;

    Rectangle_i bounds;
    bounds.setPosition({300, 200});
    bounds.setSize({400, 400});

    if (r_window.getInput().getInput(InputID::Shoot)->isDown())
    {
        LevelGenerator::Config config;
        config.bounds = bounds;
        config.roomPool.push_back({&r_assets.rooms().get(RoomID::Test), 10});
        config.initialRoomPlacementCount = 100;
        config.roomSpread                = {1, 100};
        config.roomMinSpacing            = {4, 4};

        LevelGenerator generator;
        generator.setConfig(config);
        m_roomGraph = generator.generate(Math::Random::unseededRandomInt(0, 100000));
    }

    RectangleRenderCommandData boundsData;
    boundsData.a     = bounds.getA();
    boundsData.b     = bounds.getB();
    boundsData.color = Color(255, 0, 0);
    renderCommands.push_back({0, boundsData});

    for (auto &[index, node] : m_roomGraph.getNodes())
    {
        Rectangle_i rect(index, node.value->getSize());

        RectangleRenderCommandData rdata;
        rdata.a     = rect.getA();
        rdata.b     = rect.getB();
        rdata.color = Color(255, 255, 0);
        renderCommands.push_back({1, rdata});

        for (Vec2i connection : node.connections)
        {
            SegmentRenderCommandData sdata;
            sdata.a     = index;
            sdata.b     = connection;
            sdata.color = Color(255, 255, 255);
            renderCommands.push_back({0, sdata});
        }
    }

    r_window.getViewport().render(renderCommands);
}
