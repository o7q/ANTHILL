#pragma once

#include "events/event_pool.hpp"
#include "item/context.hpp"
#include "world/entity_handler/events/base.hpp"

class IReloadable
{
  public:
    virtual bool reload(const ItemUseContext &context,
                        EventPool<EntityEvent> &eventsOut) = 0;
};
