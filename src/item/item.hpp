#pragma once

#include <string>

enum class ItemType
{
    Weapon
};

class Item
{
  public:
    Item(const std::string &name) : m_name(name) {}
    virtual ~Item() {}

    std::string getName() { return m_name; }

    virtual void actionHold() {}
    virtual void actionRelease() {}

  protected:
    const std::string m_name = "";
};
