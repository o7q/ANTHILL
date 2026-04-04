#pragma once

#include "events/entity/base.hpp"
#include "item/context.hpp"
#include "math/vec.hpp"
#include <memory>
#include <string>
#include <vector>

class Item
{
  public:
    Item(const std::string &name) : m_name(name) {}
    virtual ~Item() {}

    std::string getName() { return m_name; }

    virtual void update(float dt) = 0;
    virtual std::vector<std::unique_ptr<EntityEvent>>
    use(const ItemUseContext &context) = 0;

  protected:
    const std::string m_name = "";
    Vec2i m_gripPoint1;
    Vec2i m_gripPoint2;
};
