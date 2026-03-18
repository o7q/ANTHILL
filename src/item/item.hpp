#pragma once

#include "backend/texture/texture.hpp"
#include <string>

enum class ItemType
{
    Weapon
};

class Item
{
  public:
    Item(const std::string &name, const Texture &texture)
        : m_name(name), m_texture(texture)
    {
    }
    virtual ~Item() {}

    std::string getName() { return m_name; }

  protected:
    const std::string m_name = "";
    const Texture &m_texture;
};
