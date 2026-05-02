#pragma once

#include "identifier.hpp"

enum class SceneID
{
    None,
    Main,
    Test
};
using SceneIDKey = Identifier<SceneID>;
