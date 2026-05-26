#pragma once

#include "level_generator/room.hpp"

class TestRoom : public Room
{
  public:
    TestRoom()
    {
        InitConfig config;
        config.backgroundPath     = "assets/rooms/test/test_background.png";
        config.particleColorPath  = "assets/rooms/test/test_color.png";
        config.particleLookupPath = "assets/rooms/test/test_lookup.png";
        init(config);
    }

  private:
};
