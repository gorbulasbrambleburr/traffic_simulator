#include "global_variables.h"
#include "EventList.h"
#include "AddVehicleEvent.h"
#include "RemoveVehicleEvent.h"
#include "Vehicle.h"
#include "Street.h"


AddVehicleEvent::AddVehicleEvent(const int &time, Street *street, EventList* events, Vehicle* vehicle)
    : Event(time, street, events), m_vehicle(vehicle) {
}

AddVehicleEvent::~AddVehicleEvent() {
}

void AddVehicleEvent::makeItHappen() {

    static int vehicle_id = 1;
	
	// Check for available space
	if (m_vehicle->getLength() + 3 <= m_street->getFreeSpace()) {

		// Give it an ID if it doesn't already have one
		if (m_vehicle->getID() == -1) {
			m_vehicle->setID(vehicle_id++);
		}
		
		// Add the vehicle
		m_street->addVehicle(m_vehicle);
		
		// The distance this vehicle has to travel		
		int travel_distance = m_street->getLength() - m_vehicle->getLength() - 3;

		// Expected removal time for this vehicle
		double speed_mps = m_street->getSpeed() / 3.6;
		const int rem_time = sim_clock +  (int) ceil(travel_distance / speed_mps);
		m_vehicle->setRemTime(rem_time);
		
		// Check if it's a drain street
		if (m_street->isDrain()) {

			// Create an event to remove this vehicle
			m_events->sorted_insert(new RemoveVehicleEvent(rem_time, m_street, m_events));
		}
	}
}

