#pragma once

#include "events/entity/base.hpp"
#include "events/event_pool.hpp"
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

    virtual void reload();
    void addAmmo(int amount) { m_ammoReserve += amount; }
    void setMagazineSize(int size) { m_magazineSize = size; }
    void depleteAmmo(int amount) { m_ammoInMagazine -= amount; }
    int getAmmoInMagazine() const { return m_ammoInMagazine; }

  protected:
    virtual void fire(const ItemUseContext &context, EventPool<EntityEvent> &events) = 0;

    virtual bool restock_ammo();

  protected:
    FireMode m_fireMode = FireMode::SemiAuto;
    Vec2i m_relativeMuzzlePosition;

  private:
    int m_magazineSize   = 0;
    int m_ammoReserve    = 0;
    int m_ammoInMagazine = 0;
};
