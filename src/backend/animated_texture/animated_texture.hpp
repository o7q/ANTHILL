#pragma once

#include "backend/texture/texture.hpp"
#include "math/index.hpp"
#include <vector>

class AnimatedTexture
{
  public:
    AnimatedTexture() = default;
    AnimatedTexture(const std::filesystem::path &path, Vec2u frameSize)
    {
        Texture sheet(path);

        int frameCount = sheet.getSize().x / frameSize.x;

        for (int f = 0; f < frameCount; ++f)
        {
            std::vector<Color> pixels;
            pixels.resize(frameSize.x * frameSize.y);
            for (unsigned int y = 0; y < frameSize.y; ++y)
            {
                for (unsigned int x = 0; x < frameSize.x; ++x)
                {
                    Color sheetPx = sheet.getPixel(x + frameSize.x * f, y);
                    pixels[Math::Index::index_2dto1d(x, y, frameSize.x)] =
                        sheetPx;
                }
            }

            m_frames.push_back(Texture(pixels, frameSize.x, frameSize.y));
        }
    }
    AnimatedTexture(const AnimatedTexture &other) = default;
    AnimatedTexture &operator=(const AnimatedTexture &other) = default;
    ~AnimatedTexture() = default;

    void animate(int currentFPS)
    {
        float v = m_fps / (float)currentFPS;
        m_frameCounter += v;

        if (m_frameCounter >= 1.0f)
        {
            m_currentFrame = (m_currentFrame + 1) % m_frames.size();
            m_frameCounter = 0;
        }
    }

    void setFPS(unsigned int fps) { m_fps = fps; }

    void play() { m_playing = true; }
    void pause() { m_playing = false; }
    void stop()
    {
        m_playing = false;
        m_currentFrame = 0;
    }

    const Texture *getCurrentFrame() const { return getFrame(m_currentFrame); }

    const Texture *getFrame(unsigned int index) const
    {
        if (index >= m_frames.size())
        {
            return nullptr;
        }

        return &m_frames[index];
    }

  private:
    bool m_playing = false;
    float m_frameCounter = 0;
    unsigned int m_currentFrame = 0;
    unsigned int m_fps = 30;
    std::vector<Texture> m_frames;
};
