#pragma once

namespace WorldGenerator
{
    struct Settings
    {
        enum class Preset
        {
            Test
        };
    
        int width = 0;
        int height = 0;
    
        int seed = -1;
    
        Preset preset;
    };
}