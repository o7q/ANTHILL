#pragma once

#include "identifier.hpp"

enum class InputID
{
    Left,
    Right,
    Up,
    Down,

    Jump,

    Action1,
    Action2,

    AltAction1,
    AltAction2,
    AltAction3,
    AltAction4,
    AltAction5,
    AltAction6,
    AltAction7,
    AltAction8,
    AltAction9,
    AltAction10,

    Reload
};
using InputIDKey = Identifier<InputID>;
