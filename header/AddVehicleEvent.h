#ifndef CREATEVEHICLEEVENT_H
#define CREATEVEHICLEEVENT_H

class Street;
class EventList;

#include "Event.h"

class AddVehicleEvent : public Event {
public:
	AddVehicleEvent(const int &time, Street* street, EventList* events);
    ~AddVehicleEvent();
    void makeItHappen();
};
#endif // CREATEVEHICLEEVENT_H
