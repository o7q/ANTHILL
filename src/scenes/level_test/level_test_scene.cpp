#include "level_test_scene.hpp"

#include "core/math/geometry/rectangle.hpp"
#include "core/math/geometry/triangle.hpp"
#include "core/math/graph.hpp"
#include "core/math/mesh.hpp"
#include "core/math/random.hpp"
#include "core/viewport/render_command.hpp"
#include "level_generator/layout_generator.hpp"
#include "room/room.hpp"
#include <vector>

void LevelTestScene::onStart() {}

void LevelTestScene::onTick()
{
    std::vector<RenderCommand> renderCommands;

    if (r_window.getInput().getInput(InputID::Shoot)->isDown())
    {
        m_roomGraph.clear();

        {
            Rectangle_i bounds;
            bounds.setPosition({60, 60});
            bounds.setSize({100, 100});

            LevelLayoutGenerator::Config config;
            config.bounds = bounds;
            config.roomPool.push_back({&m_testRoom1, 1});
            config.initialRoomPlacementCount = 50;
            config.roomSpread                = {5, 5};
            config.roomMinSpacing            = {2, 2};

            LevelLayoutGenerator generator;
            generator.setConfig(config);

            NodeGraph<const Room *> rooms = generator.generate(Math::Random::unseededRandomInt(0, 100000));

            for (auto &[id, node] : rooms.getNodes())
            {
                m_roomGraph.set(id, node);
            }
        }

        {
            Rectangle_i bounds;
            bounds.setPosition({190, 170});
            bounds.setSize({90, 90});

            LevelLayoutGenerator::Config config;
            config.bounds = bounds;
            config.roomPool.push_back({&m_testRoom1, 10});
            config.roomPool.push_back({&m_testRoom2, 1});
            config.initialRoomPlacementCount = 50;
            config.roomSpread                = {5, 5};
            config.roomMinSpacing            = {0, 0};

            LevelLayoutGenerator generator;
            generator.setConfig(config);

            NodeGraph<const Room *> rooms = generator.generate(Math::Random::unseededRandomInt(0, 100000));

            for (auto &[id, node] : rooms.getNodes())
            {
                m_roomGraph.set(id, node);
            }
        }

        std::vector<Vec2i> positions;
        for (auto &[id, node] : m_roomGraph.getNodes())
        {
            positions.push_back(id);
        }

        std::vector<Triangle_i> triangulation = Math::Mesh::generateTriangulation(positions);
        m_roomGraph = Math::Graph::connectNodesFromTriangulation(triangulation, m_roomGraph);
        m_roomGraph = Math::Graph::minimumSpanningTree(m_roomGraph);
    }

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
