#pragma once

#include <vector>

#include "entity.hpp"

class LivingEntity : public Entity
{
public:
    LivingEntity(Window &window, const std::vector<World *> &worlds) : Entity(window, worlds) {}

    virtual void setPosition(float x, float y) override;
    virtual void move(float x, float y) override;

    virtual void jump(bool override = false);
    void setJumpPower(float jump_power);

    Weapon *getWeapon() const { return m_weapon; }

protected:
    float m_jump_power = 8.0f;

    Weapon *m_weapon = nullptr;
};