#pragma once

#include "item/item.hpp"
#include <memory>
#include <unordered_map>

class Inventory
{
  public:
    Inventory() = default;
    virtual ~Inventory() = default;

    void addItem(std::unique_ptr<Item> item, int slot)
    {
        if (slot < 0 || slot >= m_inventorySlots)
        {
            return;
        }
        if (m_items.count(slot) ||
            m_items.size() >= static_cast<size_t>(m_inventorySlots))
        {
            return;
        }

        m_items[slot] = std::move(item);
    }

    void removeItem(int slot)
    {
        if (slot < 0 || slot >= m_inventorySlots)
        {
            return;
        }

        m_items.erase(slot);
    }

    void swapItem(int slot1, int slot2)
    {
        if (slot1 < 0 || slot1 >= m_inventorySlots || slot2 < 0 ||
            slot2 >= m_inventorySlots || slot1 == slot2)
        {
            return;
        }

        auto it1 = m_items.find(slot1);
        auto it2 = m_items.find(slot2);

        if (it1 == m_items.end() && it2 == m_items.end())
        {
            return;
        }

        std::swap(m_items[slot1], m_items[slot2]);
    }

    const Item *getTime(int slot) const
    {
        auto it = m_items.find(slot);
        return it != m_items.end() ? it->second.get() : nullptr;
    }

  private:
    std::unordered_map<int, std::unique_ptr<Item>> m_items;
    int m_inventorySlots = 10;
};
