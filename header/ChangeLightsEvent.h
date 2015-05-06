#ifndef CHANGELIGHTSEVENT_H
#define CHANGELIGHTSEVENT_H

class Street;
class Vehicle;
class EventList;

#include "Event.h"

class ChangeLightsEvent : public Event {
public:
	ChangeLightsEvent(const int &time, Street* street, Street* second_street, EventList* events);
    ~ChangeLightsEvent();
    void makeItHappen();
	void doSomething(Street* s);

private:
	Street* m_secondStreet;  //< Pointer to the second street.
};
#endif // CHANGELIGHTSEVENT_H
