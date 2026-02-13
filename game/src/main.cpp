#include "engine/window.hpp"
int main()
{
    Window window(Vec2<uint16_t>(640, 480));

    while (true)
    {
        window.update();
    }

    return 0;
}
