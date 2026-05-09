#include "gun.hpp"

void Gun::reload() { restock_ammo(); }

bool Gun::restock_ammo()
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
