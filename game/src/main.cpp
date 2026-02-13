#include "engine/window.hpp"
int main()
{
    Window window(Vec2<uint16_t>(640, 480));

    while (!window.getEventHandler().checkEvent(
        EventHandler::EventType::WINDOW_QUIT))
    {
        window.update();
    }

    return 0;
}
