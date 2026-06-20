#include "level_test_scene.hpp"

#include "level_generator/layout_generator.hpp"
#include "px/basic_types/rectangle.hpp"
#include "px/basic_types/triangle.hpp"
#include "px/utils/graph.hpp"
#include "px/utils/random.hpp"
#include "px/utils/triangulation.hpp"
#include "px/window/render_command.hpp"
#include "room/room.hpp"
#include <vector>

void LevelTestScene::onStart() {}

void LevelTestScene::onTick()
{
    std::vector<px::RenderCommand> renderCommands;

    if (r_instance.input().getInput("shoot")->isDown())
    {
        m_roomGraph.clear();

        {
            px::Rectangle_i bounds;
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

            px::NodeGraph<const Room *> rooms =
                generator.generate(px::Utils::Random::unseededRandomInt(0, 100000));

            for (auto &[id, node] : rooms.getNodes())
            {
                m_roomGraph.set(id, node);
            }
        }

        {
            px::Rectangle_i bounds;
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

            px::NodeGraph<const Room *> rooms =
                generator.generate(px::Utils::Random::unseededRandomInt(0, 100000));

            for (auto &[id, node] : rooms.getNodes())
            {
                m_roomGraph.set(id, node);
            }
        }

        std::vector<px::Vec2i> positions;
        for (auto &[id, node] : m_roomGraph.getNodes())
        {
            positions.push_back(id);
        }

        std::vector<px::Triangle_i> triangulation =
            px::Utils::Triangulation::generateTriangulation(positions);
        m_roomGraph = px::Utils::Graph::connectNodesFromTriangulation(triangulation, m_roomGraph);
        m_roomGraph = px::Utils::Graph::minimumSpanningTree(m_roomGraph);
    }

    for (auto &[index, node] : m_roomGraph.getNodes())
    {
        px::Rectangle_i rect(index, node.value->getSize());

        px::RectangleRenderCommandData rdata;
        rdata.rectangle = rect;
        rdata.color     = px::Color(255, 255, 0);
        renderCommands.push_back({1, rdata});

        for (px::Vec2i connection : node.connections)
        {
            px::SegmentRenderCommandData sdata;
            sdata.segment = {index, connection};
            sdata.color   = px::Color(255, 255, 255);
            renderCommands.push_back({0, sdata});
        }
    }

    r_instance.window().renderCommandQueue(renderCommands);
}
