#pragma once

#include "entity/update_context.hpp"
#include "item/owner_context.hpp"
#include <string>

class Item
{
  public:
    Item(const std::string &name) : m_name(name) {}
    virtual ~Item() {}

    std::string getName() { return m_name; }

    virtual void update(const EntityUpdateContext &context,
                        const ItemOwnerContext &ownerContext) = 0;
    virtual void startUsing() = 0;
    virtual void stopUsing() = 0;

  protected:
    const std::string m_name = "";
};
