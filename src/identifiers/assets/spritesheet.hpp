#pragma once

#include "identifiers/identifier.hpp"

enum class SpriteSheetID
{
    Entity_SumiStaticHead,
    Entity_SumiStaticHeadUp45,
    Entity_SumiStaticHeadDown45,
    Entity_SumiStaticLegs,

    Entity_SumiIdleTorso,

    Entity_SumiRunHead,
    Entity_SumiRunTorso,
    Entity_SumiRunLegs,

    Entity_Wuskkogel,
    
    Item_Shotgun
};
using SpriteSheetIDKey = Identifier<SpriteSheetID>;
