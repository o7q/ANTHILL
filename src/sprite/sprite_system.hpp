#pragma once

#include "sprite/sprite_animator.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

class SpriteSystem
{
  public:
    void addAnimator(SpriteAnimator animator, const std::string &id)
    {
        m_animators.insert({id, animator});
    }

    void switchAnimator(const std::string &id, bool restartAnimation = true)
    {
        if (m_currentID == id)
        {
            return;
        }

        auto it = m_animators.find(id);
        if (it == m_animators.end())
        {
            return;
        }
        m_currentID = id;
        m_currentAnimator = &it->second;

        if (restartAnimation)
        {
            m_currentAnimator->restart();
        }
    }

    const SpriteAnimator *getCurrentAnimator() const
    {
        return m_currentAnimator;
    }

    void update(float dt)
    {
        if (!m_currentAnimator)
        {
            return;
        }

        m_currentAnimator->update(dt);
    }

  private:
    std::unordered_map<std::string, SpriteAnimator> m_animators;
    std::string m_currentID = "";
    SpriteAnimator *m_currentAnimator = nullptr;
};
