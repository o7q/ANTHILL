#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_stdinc.h>
#include <unordered_map>
class EventHandler
{
  public:
    EventHandler() {}

    void clear() { m_triggeredEvents.clear(); }
    void update(SDL_Event &event) { m_triggeredEvents[event.type] = true; }
    std::unordered_map<Uint32, bool> &getTriggeredEvents()
    {
        return m_triggeredEvents;
    }

  private:
    std::unordered_map<Uint32, bool> m_triggeredEvents;
};
