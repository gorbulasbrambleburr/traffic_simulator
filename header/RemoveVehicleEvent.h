#ifndef REMOVEVEHICLEEVENT_H
#define REMOVEVEHICLEEVENT_H

class Street;
class Vehicle;

#include "Event.h"

class RemoveVehicleEvent : public Event {

public:
	RemoveVehicleEvent(const int &time, Street* street);
	~RemoveVehicleEvent();
	void makeItHappen();
};
#endif // REMOVEVEHICLEEVENT_H
