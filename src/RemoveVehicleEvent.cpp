#include "RemoveVehicleEvent.h"

RemoveVehicleEvent::RemoveVehicleEvent(const int &time, Street *street, Vehicle* vehicle)
    : Event(time, street), m_vehicle(vehicle) {
}

RemoveVehicleEvent::~RemoveVehicleEvent() {
}

void RemoveVehicleEvent::makeItHappen() {

	// Drain street removal
	//TODO(mak)



	// "Change streets" kind of removal
	// Every time we remove a vehicle we create a new
	// RemoveVehicleEvent for the next vehicle on the street.
	//TODO(mak)
}