#pragma once

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

    virtual bool reload(const ItemUseContext &context,
                        EventPool<EntityEvent> &eventsOut) override
    {
        return restock_ammo();
    }

    void addAmmo(int amount) { m_ammoReserve += amount; }
    void depleteAmmo() { m_ammoInMagazine--; }
    int getAmmoInMagazine() { return m_ammoInMagazine; }
    int getAmmoInReserve() { return m_ammoReserve; }
    void setMagazineSize(int size) { m_magazineSize = size; }

  protected:
    virtual void fire(const ItemUseContext &context,
                      EventPool<EntityEvent> &eventsOut) = 0;

    virtual bool restock_ammo()
    {
        if (m_ammoReserve <= 0)
        {
            return false;
        }

        int refillAmount = m_magazineSize - m_ammoInMagazine;

        if (refillAmount <= 0)
        {
            return false;
        }

        if (refillAmount > m_ammoReserve)
        {
            m_ammoInMagazine += m_ammoReserve;
            m_ammoReserve = 0;
        }
        else
        {
            m_ammoInMagazine = m_magazineSize;
            m_ammoReserve -= refillAmount;
        }

        return true;
    }

  protected:
    FireMode m_fireMode = FireMode::SemiAuto;
    Vec2i m_muzzlePosition;

  private:
    int m_ammoReserve = 0;
    int m_ammoInMagazine = 0;
    int m_magazineSize = 0;
};
