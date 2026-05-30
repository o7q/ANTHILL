#include "rooms.hpp"
#include "identifiers/rooms.hpp"
#include "rooms/sand_small.hpp"
#include <memory>

void initRooms(AssetPool<RoomID, Room> &assets)
{
    std::unordered_map<RoomID, std::unique_ptr<Room>> v;

    v[RoomID::SandSmall] = std::make_unique<SandSmallRoom>();

    for (auto &[id, data] : v)
    {
        assets.add(id, std::move(data));
    }
}
