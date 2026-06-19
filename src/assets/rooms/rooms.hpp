#pragma once

#include "px/asset_pool/asset_pool.hpp"
#include "identifiers/rooms.hpp"
#include "room/room.hpp"

void initRooms(AssetPool<RoomID, Room> &assets);
