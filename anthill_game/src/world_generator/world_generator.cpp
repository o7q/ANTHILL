#include "world_generator.hpp"

World *WorldGenerator::generate(SDL_Renderer *renderer, Settings settings)
{
    Generator *generator = nullptr;

    switch (settings.preset)
    {
    case Settings::Preset::Test:
        generator = new TestGenerator(renderer, settings);
        break;
    }

    if (generator == nullptr)
    {
        return nullptr;
    }

    World *world = generator->world();
    delete generator;

    return world;
}