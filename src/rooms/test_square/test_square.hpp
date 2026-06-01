#pragma once

#include "room/room.hpp"

class TestSquareRoom : public Room
{
  public:
    TestSquareRoom();

    void writeToLayer(Vec2i worldTopLeft, ChunkMap<StructurePositionalSpawnData> &dataOut) const override;
};
