#include "textures.hpp"

void initBackgrounds(std::unordered_map<TextureIDKey, TextureLoadData> &v)
{
    const std::string base = "assets/textures/backgrounds/";

    v[TextureID::SandBackground]  = {base + "sand.png"};
    v[TextureID::SandBackground2] = {base + "sand2.png"};
}
