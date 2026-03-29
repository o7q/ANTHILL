#pragma once

#include "entities/projectile/projectile.hpp"
#include "item/item.hpp"
#include <memory>
#include <vector>

class Gun : public Item
{
  public:
    enum class FireMode
    {
        FullAuto,
        SemiAuto,
        Burst
    };

  public:
    Gun(const std::string &name) : Item(name) {}

    virtual void actionHold() override
    {
        if (!m_canShoot)
        {
            return;
        }

        fire();

        if (m_ammoInMagazine > 0)
        {
            m_ammoInMagazine--;
        }

        if (m_fireMode == FireMode::SemiAuto)
        {
            m_canShoot = false;
        }
    }
    virtual void actionRelease() override { m_canShoot = true; }
    virtual void reload()
    {
        int refillAmount = m_magazineSize - m_ammoInMagazine;

        if (refillAmount > m_ammoReserve)
        {
            return;
        }

        m_ammoReserve -= refillAmount;
        m_ammoInMagazine = m_magazineSize;
    }

    void addAmmo(int amount) { m_ammoReserve += amount; }
    void setFireMode(FireMode mode) { m_fireMode = mode; }

    std::vector<std::unique_ptr<Projectile>> getEmittedProjectiles()
    {
        return m_emittedProjectiles;
    }

  protected:
    virtual void fire() = 0;

  private:
    int m_ammoReserve = 0;
    int m_ammoInMagazine = 0;
    int m_magazineSize = 0;

    bool m_canShoot = true;

    FireMode m_fireMode = FireMode::SemiAuto;

    std::vector<std::unique_ptr<Projectile>> m_emittedProjectiles;
};
