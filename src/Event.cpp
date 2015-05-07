// Forwarded declarations
class Street;
class EventList;

#include "Event.h"


Event::Event(const int &time, Street* street, EventList* events)
    : m_time(time), m_street(street), m_events(events) {
}

Event::~Event() {
}

int Event::getTime() {
    return m_time;
}
