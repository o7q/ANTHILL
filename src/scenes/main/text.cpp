#include "main_scene.hpp"

void MainScene::renderText(std::vector<RenderCommand> &renderCommands)
{
    Player *player = m_world.getEntityHandler().getCurrentPlayer();

    if (player)
    {
        healthText = r_assets.fonts()
                         .get(FontID::Default)
                         .generateStringTexture(std::to_string((int)player->getHealth()),
                                                Color(255, 100, 100), 5, 1, 8);

        TextureRenderCommandData healthRenderData;
        healthRenderData.texture  = &healthText;
        healthRenderData.position = {5, 25};
        healthRenderData.origin   = {0, 0};
        renderCommands.push_back({1000, healthRenderData});
    }

    fpsText = r_assets.fonts()
                  .get(FontID::Default)
                  .generateStringTexture(std::to_string((int)r_window.getTime().getInfo().fps),
                                         Color(0, 255, 0), 5, 1, 8);

    TextureRenderCommandData fpsRenderData;
    fpsRenderData.texture  = &fpsText;
    fpsRenderData.position = {5, 5};
    fpsRenderData.origin   = {0, 0};
    renderCommands.push_back({1000, fpsRenderData});

    entitiesText = r_assets.fonts()
                       .get(FontID::Default)
                       .generateStringTexture(std::to_string(m_world.getEntityHandler().getEntityCount()),
                                              Color(255, 100, 255), 5, 1, 8);

    TextureRenderCommandData entitiesRenderData;
    entitiesRenderData.texture  = &entitiesText;
    entitiesRenderData.position = {5, 15};
    entitiesRenderData.origin   = {0, 0};

    chunksText = r_assets.fonts()
                     .get(FontID::Default)
                     .generateStringTexture(
                         std::to_string(m_world.getParticleHandler().getParticles().getChunks().size()),
                         Color(255, 100, 0), 5, 1, 8);
    renderCommands.push_back({1000, entitiesRenderData});

    TextureRenderCommandData chunkRenderData;
    chunkRenderData.texture  = &chunksText;
    chunkRenderData.position = {5, 35};
    chunkRenderData.origin   = {0, 0};

    renderCommands.push_back({1000, chunkRenderData});
}
