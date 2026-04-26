#pragma once

#include "sprite/sprite_animator.hpp"
#include "sprite/sprite_animator_group.hpp"
#include <unordered_map>

template <typename BodyPartID, typename AnimationID> class CharacterSprite
{
  public:
    void update(float dt)
    {
        for (auto &[_, animatorGroup] : m_bodyParts)
        {
            animatorGroup.update(dt);
        }
    }

    void switchAnimation(AnimationID id)
    {
        for (auto &[_, animatorGroup] : m_bodyParts)
        {
            animatorGroup.switchAnimator(id);
        }
    }

    const SpriteAnimator *getBodyPartAnimator(BodyPartID id) const
    {
        auto it = m_bodyParts.find(id);

        if (it == m_bodyParts.end())
        {
            return nullptr;
        }

        return it->second.getCurrentAnimator();
    }

  protected:
    void add_animation(BodyPartID bodyPartID, AnimationID animationID,
                       const SpriteAnimator &animator)
    {
        m_bodyParts[bodyPartID].addAnimator(animator, animationID);
    }

  private:
    std::unordered_map<BodyPartID, SpriteAnimatorGroup<AnimationID>>
        m_bodyParts;
};
