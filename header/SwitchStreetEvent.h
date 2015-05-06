#ifndef SWITCHSTREETEVENT_H
#define SWITCHSTREETEVENT_H

class Street;
class Vehicle;
class EventList;

#include "Event.h"

class SwitchStreetEvent : public Event {
public:
	SwitchStreetEvent(const int &time, Street* street, EventList* events, Vehicle* vehicle);
    ~SwitchStreetEvent();
    void makeItHappen();

private:
	Vehicle* m_vehicle;      //< The vehicle to be switched.
};
#endif // SWITCHSTREETEVENT_H
