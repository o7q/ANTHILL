#pragma once

#include "utils.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_stdinc.h>
#include <vector>
class EventHandler
{
  public:
    enum class EventType
    {
        WINDOW_QUIT
    };

  public:
    EventHandler() = default;
    EventHandler(const EventHandler &other) = delete;
    EventHandler &operator=(const EventHandler &other) = delete;

    void begin() { m_triggeredEvents.clear(); }
    void update(SDL_Event &event)
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            m_triggeredEvents.push_back(EventType::WINDOW_QUIT);
            break;
        }
    }

    bool checkEvent(EventType eventType) const
    {
        return Utils::doesVectorContain(m_triggeredEvents, eventType);
    }

  private:
    std::vector<EventType> m_triggeredEvents;
};
