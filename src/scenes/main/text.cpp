#include "main_scene.hpp"

void MainScene::renderText(std::vector<RenderCommand> &renderCommands)
{
    Player *player = m_world.getEntityHandler().getCurrentPlayer();

    if (player)
    {
        m_healthText = r_assets.fonts()
                         .get(FontID::Default)
                         .generateTexture({std::to_string((int)player->getHealth()), Color(255, 100, 100)});

        TextureRenderCommandData healthRenderData;
        healthRenderData.texture  = &m_healthText;
        healthRenderData.position = {5, 25};
        healthRenderData.origin   = {0, 0};
        renderCommands.push_back({1000, healthRenderData});
    }

    m_fpsText = r_assets.fonts()
                  .get(FontID::Default)
                  .generateTexture({std::to_string((int)r_window.getTime().getInfo().fps), Color(0, 255, 0)});

    TextureRenderCommandData fpsRenderData;
    fpsRenderData.texture  = &m_fpsText;
    fpsRenderData.position = {5, 5};
    fpsRenderData.origin   = {0, 0};
    renderCommands.push_back({1000, fpsRenderData});

    m_entitiesText = r_assets.fonts()
                       .get(FontID::Default)
                       .generateTexture({std::to_string(m_world.getEntityHandler().getEntityCount()),
                                         Color(255, 100, 255)});

    TextureRenderCommandData entitiesRenderData;
    entitiesRenderData.texture  = &m_entitiesText;
    entitiesRenderData.position = {5, 15};
    entitiesRenderData.origin   = {0, 0};

    m_chunksText =
        r_assets.fonts()
            .get(FontID::Default)
            .generateTexture({std::to_string(m_world.getParticleHandler().getParticles().getChunks().size()),
                              Color(255, 100, 0)});
    renderCommands.push_back({1000, entitiesRenderData});

    TextureRenderCommandData chunkRenderData;
    chunkRenderData.texture  = &m_chunksText;
    chunkRenderData.position = {5, 35};
    chunkRenderData.origin   = {0, 0};

    renderCommands.push_back({1000, chunkRenderData});
}
