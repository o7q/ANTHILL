#pragma once

#include "backend/timer/timer.hpp"
#include "item/item.hpp"
#include "item/reloadable.hpp"

class Gun : public Item, public IReloadable
{
  public:
    enum class FireMode
    {
        FullAuto,
        SemiAuto
    };

  public:
    Gun(const std::string &name) : Item(name) {}

    virtual void reload() override
    {
        if (m_ammoInMagazine > m_magazineSize)
        {
            m_ammoInMagazine = m_magazineSize;
        }

        int refillAmount = m_magazineSize - m_ammoInMagazine;

        if (refillAmount > m_ammoReserve)
        {
            m_ammoInMagazine = m_ammoInMagazine + m_ammoReserve;
            m_ammoReserve = 0;
        }
        else
        {
            m_ammoInMagazine = m_magazineSize;
            m_ammoReserve -= refillAmount;
        }
    }

    void addAmmo(int amount) { m_ammoReserve += amount; }
    void depleteAmmo() { m_ammoInMagazine--; }
    int getAmmoInMagazine() { return m_ammoInMagazine; }
    int getAmmoInReserve() { return m_ammoReserve; }
    void setMagazineSize(int size) { m_magazineSize = size; }

  protected:
    virtual std::vector<std::unique_ptr<EntityEvent>>
    fire(const ItemUseContext &context) = 0;

  protected:
    FireMode m_fireMode = FireMode::SemiAuto;
    Vec2i m_muzzlePosition;

  private:
    int m_ammoReserve = 0;
    int m_ammoInMagazine = 0;
    int m_magazineSize = 0;
};
