#pragma once

#include "item/item.hpp"
#include <memory>
#include <unordered_map>

class Inventory
{
  public:
    Inventory() = default;
    virtual ~Inventory() = default;

    void addItem(std::unique_ptr<Item> item, unsigned int slot)
    {
        if (slot >= m_inventorySlots || m_items.count(slot))
        {
            return;
        }

        m_items[slot] = std::move(item);
    }

    void removeItem(unsigned int slot)
    {
        if (slot >= m_inventorySlots)
        {
            return;
        }

        m_items.erase(slot);
    }

    void swapItem(unsigned int slot1, unsigned int slot2)
    {
        if (slot1 >= m_inventorySlots || slot2 >= m_inventorySlots ||
            slot1 == slot2)
        {
            return;
        }

        auto it1 = m_items.find(slot1);
        auto it2 = m_items.find(slot2);

        if (it1 == m_items.end() || it2 == m_items.end())
        {
            return;
        }
        std::swap(m_items[slot1], m_items[slot2]);
    }

    Item *getItem(int slot)
    {
        auto it = m_items.find(slot);
        return it != m_items.end() ? it->second.get() : nullptr;
    }

    Item *getSelectedItem() { return getItem(m_selectedSlot); }

  private:
    std::unordered_map<int, std::unique_ptr<Item>> m_items;
    unsigned int m_inventorySlots = 10;
    unsigned int m_selectedSlot = 0;
};
