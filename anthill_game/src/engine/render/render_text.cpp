#include "render_manager.hpp"

void RenderManager::renderText(TTF_Font *font, const std::string &text, Vec2<int> position, Color color, Camera *camera)
{
    if (font == nullptr)
    {
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), text.size(), SDL_Color{color.r, color.g, color.b, color.a});

    Texture texture(m_renderer, surface);
    texture.setPosition(position.x, position.y);
    texture.setOrigin(0, 0);
    SDL_DestroySurface(surface);

    renderTexture(&texture, camera);
}