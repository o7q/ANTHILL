#pragma once

#include "identifiers/identifier.hpp"

enum class SpriteSheetID
{
    Entity_SumiIdleHead,
    Entity_SumiIdleHeadUp45,
    Entity_SumiIdleHeadDown45,
    Entity_SumiIdleTorso,
    Entity_SumiIdleLegs,
    Entity_SumiRunHead,
    Entity_SumiRunTorso,
    Entity_SumiRunLegs,

    Entity_Wuskkogel,
    Item_Shotgun
};
using SpriteSheetIDKey = Identifier<SpriteSheetID>;
