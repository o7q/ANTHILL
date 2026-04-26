#pragma once

#include "sprite/sprite_animator.hpp"
#include <unordered_map>

template <typename AnimationID> class SpriteAnimatorGroup
{
  public:
    void addAnimator(SpriteAnimator animator, AnimationID id)
    {
        m_animators.insert({id, animator});
    }

    void switchAnimator(AnimationID id, bool restartAnimation = true)
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
    std::unordered_map<AnimationID, SpriteAnimator> m_animators;
    std::optional<AnimationID> m_currentID;
    SpriteAnimator *m_currentAnimator = nullptr;
};
