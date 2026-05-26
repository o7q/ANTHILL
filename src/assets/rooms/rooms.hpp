#pragma once

#include "core/asset_pool/asset_pool.hpp"
#include "identifiers/rooms.hpp"
#include "level_generator/room.hpp"

void initRooms(AssetPool<RoomID, Room> &assets);
