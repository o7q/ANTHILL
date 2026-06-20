#pragma once

#include "room/room.hpp"

class TestTallRoom : public Room
{
  public:
    TestTallRoom();

    void writeToLayer(px::Vec2i worldTopLeft,
                      px::ChunkMap<StructurePositionalSpawnData> &dataOut) const override;
};
