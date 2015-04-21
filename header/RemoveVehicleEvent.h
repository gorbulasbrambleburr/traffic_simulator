#ifndef REMOVEVEHICLEEVENT_H
#define REMOVEVEHICLEEVENT_H

class Street;
class Vehicle;

#include "Event.h"

class RemoveVehicleEvent : public Event {

public:
	RemoveVehicleEvent(const int &time, Street* street, Vehicle* vehicle);
	~RemoveVehicleEvent();
	void makeItHappen();

private:
	Vehicle* m_vehicle;  //< The vehicle to be removed.
};
#endif // REMOVEVEHICLEEVENT_H
