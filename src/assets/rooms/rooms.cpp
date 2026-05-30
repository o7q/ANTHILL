#include "rooms.hpp"
#include "identifiers/rooms.hpp"
#include "rooms/sand_room.hpp"
#include <memory>

void initRooms(AssetPool<RoomID, Room> &assets)
{
    std::unordered_map<RoomID, std::unique_ptr<Room>> v;

    v[RoomID::Sand] = std::make_unique<SandRoom>();

    for (auto &[id, data] : v)
    {
        assets.add(id, std::move(data));
    }
}
