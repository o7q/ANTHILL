#pragma once

#include "item/item.hpp"

class Weapon : public Item
{
  public:
    Weapon(const std::string &name, const Texture &texture)
        : Item(name, texture)
    {
    }
    virtual ~Weapon() {}
};
