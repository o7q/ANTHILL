#pragma once

#include "identifiers/identifier.hpp"

enum class SpriteSheetID
{
    Entity_SumiIdle,
    Entity_SumiRun,
    Entity_SumiIdleToRun,
    Entity_Wuskkogel,
    Item_Shotgun
};
using SpriteSheetIDKey = Identifier<SpriteSheetID>;
