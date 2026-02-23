#include "event_handler.hpp"

#include "engine/utils/data.hpp"

void EventHandler::resetEvents() { m_triggeredEvents.clear(); }

void EventHandler::poll(SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_EVENT_QUIT:
        m_triggeredEvents.push_back(EventType::WINDOW_QUIT);
        break;
    }
}

bool EventHandler::didEventOccur(EventType eventType) const
{
    return DataUtils::doesVectorContain(m_triggeredEvents, eventType);
}
