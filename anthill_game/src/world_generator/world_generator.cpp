#include "world_generator.hpp"

WorldGenerator::ThreadSafeGenerator::ThreadSafeGenerator(Settings settings)
{
    m_settings = settings;
}

void WorldGenerator::ThreadSafeGenerator::generate()
{
    Generator *generator = nullptr;

    switch (m_settings.preset)
    {
    case Settings::Preset::Jungle:
        generator = new JungleGenerator(m_settings);
        break;
    }

    if (generator == nullptr)
    {
        return;
    }

    m_world = generator->world();
    delete generator;

    m_finished = true;
}

bool WorldGenerator::ThreadSafeGenerator::finished()
{
    return m_finished;
}

World *WorldGenerator::ThreadSafeGenerator::getWorld()
{
    return m_world;
}