#pragma once

#include "sprite/sprite_animator_group.hpp"
#include <unordered_map>

template <typename GroupID> class SpriteSystem
{
  public:
    void update(float dt)
    {
        for (auto &[_, animatorGroup] : m_animatorGroups)
        {
            animatorGroup.update(dt);
        }
    }

    const SpriteAnimatorGroup<GroupID> *
    getAnimatorGroup(const GroupID &id) const
    {
        auto it = m_animatorGroups.find(id);

        if (it == m_animatorGroups.end())
        {
            return nullptr;
        }

        return it->second.getCurrentAnimator();
    }

  private:
    std::unordered_map<GroupID, SpriteAnimatorGroup<std::string>>
        m_animatorGroups;
};
