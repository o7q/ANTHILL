#pragma once

#include "room/room.hpp"

class TestTallRoom : public Room
{
  public:
    TestTallRoom();

    void writeToLayer(Vec2i worldTopLeft, ChunkMap<StructurePositionalSpawnData> &dataOut) const override;
};
