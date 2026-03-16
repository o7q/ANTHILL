#pragma once

#include "item/weapon/weapon.hpp"

class Gun : public Weapon
{
  public:
    enum class FireMode
    {
        FullAuto,
        SemiAuto,
        Burst
    };

  public:
    virtual void shoot()
    {
        if (m_ammoInMagazine > 0)
        {
            m_ammoInMagazine--;
        }
    }
    virtual void reload()
    {
        int refillAmount = m_magazineSize - m_ammoInMagazine;
        m_ammoReserve -= refillAmount;
        m_ammoInMagazine = m_magazineSize;
    }

    void addAmmo(int amount) { m_ammoReserve += amount; }
    void setFireMode(FireMode mode) { m_fireMode = mode; }

  private:
    int m_ammoReserve = 0;
    int m_ammoInMagazine = 0;
    int m_magazineSize = 0;

    FireMode m_fireMode = FireMode::SemiAuto;
};
