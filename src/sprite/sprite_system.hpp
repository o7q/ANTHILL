#pragma once

#include "px/basic_types/vec.hpp"
#include "sprite/sprite_animator.hpp"
#include <optional>
#include <unordered_map>

class SpriteAnimatorPositional
{
  public:
    SpriteAnimatorPositional(SpriteAnimator animator, px::Vec2Opt_i origin, px::Vec2i offset)
        : m_animator(animator)
    {
        m_origin = origin;
        m_offset = offset;
    }

    SpriteAnimator &getAnimator() { return m_animator; }
    const SpriteAnimator &getAnimator() const { return m_animator; }

    px::Vec2Opt_i getOrigin() const { return m_origin; }
    px::Vec2i getOffset() const { return m_offset; }

  private:
    SpriteAnimator m_animator;

    px::Vec2Opt_i m_origin;
    px::Vec2i m_offset;
};

template <typename AnimationID> class SpriteSystem
{
  public:
    void addAnimator(const AnimationID &id, SpriteAnimatorPositional animator)
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

        m_currentID       = id;
        m_currentAnimator = &it->second;
    }

    const SpriteAnimatorPositional *getCurrentAnimator() const { return m_currentAnimator; }

    void update(float dt)
    {
        for (auto &[_, animator] : m_animators)
        {
            animator.getAnimator().update(dt);
        }
    }

    void restartAll()
    {
        for (auto &[_, animator] : m_animators)
        {
            animator.getAnimator().restart();
        }
    }

  private:
    std::unordered_map<AnimationID, SpriteAnimatorPositional> m_animators;
    std::optional<AnimationID> m_currentID;
    SpriteAnimatorPositional *m_currentAnimator = nullptr;
};
