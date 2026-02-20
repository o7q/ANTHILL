#include "event_handler.hpp"

#include "utils.hpp"

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
    return Utils::doesVectorContain(m_triggeredEvents, eventType);
}
