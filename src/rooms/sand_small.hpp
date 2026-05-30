#pragma once

#include "room/room.hpp"

class SandSmallRoom : public Room
{
  public:
    SandSmallRoom();

    void writeToLayer(Vec2i worldTopLeft, ChunkMap<StructurePositionalSpawnData> &dataOut) const override;
};
