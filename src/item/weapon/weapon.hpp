#pragma once

#include "item/item.hpp"

class Weapon : public Item
{
  public:
    Weapon(const std::string &name) : Item(name) {}
    virtual ~Weapon() {}
};
