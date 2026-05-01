#pragma once

#include "events/entity/base.hpp"
#include "events/event_pool.hpp"
#include "item/context.hpp"

class IReloadable
{
  public:
    virtual bool reload(const ItemUseContext &context, EventPool<EntityEvent> &eventsOut) = 0;
};
