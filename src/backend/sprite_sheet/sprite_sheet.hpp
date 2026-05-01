#pragma once

#include "backend/texture/texture.hpp"
#include <vector>

class SpriteSheet
{
  public:
    SpriteSheet() = default;
    SpriteSheet(const std::filesystem::path &path, Vec2u spriteSize);
    SpriteSheet(const SpriteSheet &other)            = default;
    SpriteSheet &operator=(const SpriteSheet &other) = default;
    ~SpriteSheet()                                   = default;

    const Texture *getSprite(unsigned int index) const;
    unsigned int getSpriteCount() const { return m_frames.size(); }

  private:
    std::vector<Texture> m_frames;
};
