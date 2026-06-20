#pragma once

#include "ai/navigation/ai_navigation.hpp"
#include "ai/perception/ai_perception.hpp"
#include "entity/body/entity_body.hpp"
#include "entity/update_context.hpp"
#include "events/entity/base.hpp"

enum class WuskkogelStateID
{
    Roam,
    Follow,
    Attack
};

struct UpdateContext
{
    const EntityUpdateContext &context;
    EventPool<EntityEvent> &events;

    EntityBody &body;
    AIPerception &perception;
    AINavigation &navigation;
    float &lookAngle;
    px::Vec2i &headPos;
};
