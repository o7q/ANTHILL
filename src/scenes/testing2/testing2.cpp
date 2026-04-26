#include "testing2.hpp"
#include "backend/viewport/render_command.hpp"
#include "math/color.hpp"
#include "math/numbers.hpp"
#include "math/perlin.hpp"
#include "math/random.hpp"
#include "math/vec.hpp"
#include <vector>

void TestScene2::onStart() {}

void TestScene2::onTick()
{
    std::vector<RenderCommand> renderCommands;

    if (r_input.getInput(InputID::Action1)->isDown())
    {
        m_screen.clear();

        int seed = Math::Random::weakRandInt(0, 200);

        for (unsigned int y = 0; y < m_screen.getSize().y; ++y)
        {
            for (unsigned int x = 0; x < m_screen.getSize().x; ++x)
            {
                float v =
                    Math::Perlin::sampleEx(Vec2f(x, y), {20, 20}, 10, seed) -
                    0.5f;
                float v3 = Math::Perlin::sampleEx(Vec2f(x, y), {200, 200}, 2,
                                                  seed + 2) -
                           0.5f;

                int modifier = static_cast<int>(
                    v * 50.0f + std::sinf(y * v3 / 20.0f) * 100.0f);

                if (Math::Numbers::between((int)(x + modifier), 200, 220))
                {
                    m_screen.setPixel({x, y}, Color(255, 255, 50));
                }
                else
                {
                    m_screen.setPixel({x, y}, Color(50, 50, 255));
                }
            }
        }
    }

    TextureRenderCommandData data;
    data.texture = &m_screen;
    data.origin = {0, 0};

    renderCommands.push_back({0, data});

    r_viewport.render(renderCommands);
}
