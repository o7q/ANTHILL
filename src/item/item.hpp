#pragma once

#include "events/entity/base.hpp"
#include "events/event_pool.hpp"
#include "item/context.hpp"
#include "math/vec.hpp"
#include <string>

class Item
{
  public:
    Item(const std::string &name) : m_name(name) {}
    virtual ~Item() {}

    std::string getName() { return m_name; }

    virtual void update(float dt) = 0;
    virtual void use(const ItemUseContext &context,
                     EventPool<EntityEvent> &eventsOut) = 0;

  protected:
    const std::string m_name = "";
    Vec2i m_gripPoint1;
    Vec2i m_gripPoint2;
};
