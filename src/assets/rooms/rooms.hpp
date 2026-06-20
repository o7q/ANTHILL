#pragma once

#include "identifiers/rooms.hpp"
#include "px/asset_pool/asset_pool.hpp"
#include "room/room.hpp"

void initRooms(px::AssetPool<RoomID, Room> &assets);
