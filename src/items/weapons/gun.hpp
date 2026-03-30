#pragma once

#include "entity/update_context.hpp"
#include "item/item.hpp"
#include "item/owner_context.hpp"
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

    virtual void update(const EntityUpdateContext &entityContext,
                        const ItemOwnerContext &ownerContext) override
    {
        if (!m_canShoot)
        {
            return;
        }

        fire(ownerContext);

        if (m_ammoInMagazine > 0)
        {
            m_ammoInMagazine--;
        }

        if (m_fireMode == FireMode::SemiAuto)
        {
            m_canShoot = false;
        }
    }

    virtual void startUsing() override { m_canShoot = true; }
    virtual void stopUsing() override { m_canShoot = false; }
    virtual void reload() override
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

  protected:
    virtual void fire(const ItemOwnerContext &ownerContext) = 0;

    FireMode m_fireMode = FireMode::SemiAuto;
  private:
    int m_ammoReserve = 0;
    int m_ammoInMagazine = 0;
    int m_magazineSize = 0;

    bool m_canShoot = false;

    float m_fireRate = 1.0f;
};
