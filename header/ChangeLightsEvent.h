#ifndef CHANGELIGHTSEVENT_H
#define CHANGELIGHTSEVENT_H

class Street;
class Vehicle;
class EventList;

#include "Event.h"

class ChangeLightsEvent : public Event {
public:
	ChangeLightsEvent(const int &time, Street* street, EventList* events);
    ~ChangeLightsEvent();
    void makeItHappen();
};
#endif // CHANGELIGHTSEVENT_H
