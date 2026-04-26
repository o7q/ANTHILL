#pragma once

#include "sprite/sprite_animator.hpp"
#include <iostream>
#include <optional>
#include <unordered_map>

template <typename AnimationID> class SpriteAnimatorGroup
{
  public:
    void addAnimator(SpriteAnimator animator, const AnimationID &id)
    {
        m_animators.insert({id, animator});
    }

    void switchAnimator(const AnimationID &id, bool transition = false)
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
        SpriteAnimator *oldAnimator = m_currentAnimator;
        m_currentAnimator = &it->second;

        if (oldAnimator && transition)
        {
            m_currentAnimator->transitionFrom(*oldAnimator);
        }
        else
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
    const AnimationID &getCurrentID() const { return m_currentID; }

  private:
    std::unordered_map<AnimationID, SpriteAnimator> m_animators;
    std::optional<AnimationID> m_currentID;
    SpriteAnimator *m_currentAnimator = nullptr;
};
