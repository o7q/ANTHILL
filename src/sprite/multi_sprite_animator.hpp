#pragma once

#include "sprite/sprite_animator.hpp"
#include <string>
#include <unordered_map>

class MultiSpriteAnimator
{
  public:
    MultiSpriteAnimator() = default;

    void add(const SpriteAnimator &animator, const std::string &id)
    {
        m_animators.emplace(id, animator);
    }

    SpriteAnimator *getCurrentAnimator()
    {
        return m_currentAnimator;
    }

    void switchAnimation(const std::string &id)
    {
        auto it = m_animators.find(id);
        if (it == m_animators.end())
        {
            return;
        }
        m_currentAnimator = &it->second;
    }

  private:
    std::string m_currentID = "";
    std::unordered_map<std::string, SpriteAnimator> m_animators;
    SpriteAnimator *m_currentAnimator = nullptr;
};
