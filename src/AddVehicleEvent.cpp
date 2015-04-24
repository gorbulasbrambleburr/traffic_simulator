#include "global_variables.h"
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

    // Check for available space
	if (m_vehicle->getLength() + 3 <= m_street->getFreeSpace()) {

		// Add the vehicle
		m_street->addVehicle(m_vehicle);

		// The distance this vehicle has to travel		
		int travel_distance = m_street->getLength() - m_vehicle->getLength() - 3;

		// Expected removal time for this vehicle
		const int rem_time = sim_clock +  travel_distance / m_street->getSpeed();
		m_vehicle->setRemTime(rem_time);

		// Log vehicle insertion
        logfile << "\nNew vehicle added to street " << m_street->getName()
                << " at time " << sim_clock;
	}
}

