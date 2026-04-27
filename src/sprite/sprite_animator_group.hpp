#pragma once

#include "sprite/sprite_animator.hpp"
#include <optional>
#include <unordered_map>

template <typename AnimationID> class SpriteAnimatorGroup
{
  public:
    void addAnimator(SpriteAnimator animator, const AnimationID &id)
    {
        m_animators.insert({id, animator});
    }

    void switchAnimator(const AnimationID &id)
    {
        if (m_currentID.has_value() && m_currentID.value() == id)
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
    }

    const SpriteAnimator *getCurrentAnimator() const
    {
        return m_currentAnimator;
    }

    void update(float dt)
    {
        for (auto &[_, animator] : m_animators)
        {
            animator.update(dt);
        }
    }

    void restartAll()
    {
        for (auto &[_, animator] : m_animators)
        {
            animator.restart();
        }
    }

  private:
    std::unordered_map<AnimationID, SpriteAnimator> m_animators;
    std::optional<AnimationID> m_currentID;
    SpriteAnimator *m_currentAnimator = nullptr;
};
