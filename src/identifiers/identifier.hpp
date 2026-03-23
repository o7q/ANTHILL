#pragma once

#include <string>
#include <variant>

template <typename TypeID> using Identifier = std::variant<TypeID, std::string>;
