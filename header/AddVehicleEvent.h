#ifndef CREATEVEHICLEEVENT_H
#define CREATEVEHICLEEVENT_H

class Street;
class Vehicle;
class EventList;

#include "Event.h"

class AddVehicleEvent : public Event {
public:
	AddVehicleEvent(const int &time, Street* street, EventList* events, Vehicle* vehicle);
    ~AddVehicleEvent();
    void makeItHappen();

private:
	Vehicle* m_vehicle;      //< The vehicle to be added.
};
#endif // CREATEVEHICLEEVENT_H
