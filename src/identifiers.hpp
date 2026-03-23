#pragma once

#include <string>
#include <variant>

template <typename TypeID> using Identifier = std::variant<TypeID, std::string>;

enum class SceneID
{
    Testing
};

enum class InputID
{
    Left,
    Right,
    Up,
    Down,

    Jump,

    Action1,
    Action2,

    SecondaryAction1,
    SecondaryAction2,
    SecondaryAction3,
    SecondaryAction4,
    SecondaryAction5,

    Debug1
};
using InputIDKey = Identifier<InputID>;

enum class TextureID
{
    Noodle,
    Pistol,
    PistolSmall,
    Character,
    Carter
};
using TextureIDKey = Identifier<TextureID>;

enum class FontID
{
    Test
};
using FontIDKey = Identifier<FontID>;
