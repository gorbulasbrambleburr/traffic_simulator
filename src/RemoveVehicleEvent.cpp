#include <cmath>
#include "global_variables.h"
#include "RemoveVehicleEvent.h"
#include "AddVehicleEvent.h"
#include "Street.h"

RemoveVehicleEvent::RemoveVehicleEvent(const int &time, Street *street)
    : Event(time, street) {
}

RemoveVehicleEvent::~RemoveVehicleEvent() {
}

void RemoveVehicleEvent::makeItHappen() {

	// Get pointer to first vehicle
	Vehicle* vehicle = m_street->peek();
	
	if (m_street->isDrain()) {

		// Drain street removal
		m_street->removeVehicle();

		// This vehicle won't be used anymore
		delete(vehicle);

		// Log it
		logfile << "\nVehicle removed at " << m_street->getName()
			    << " at time " << sim_clock;

	} else {

		// Every time we remove a vehicle we create a new
		// RemoveVehicleEvent for the next vehicle on the street.		

		// Get destination street
		int route = vehicle->getRoute();
		Street* dest_street = m_street->getDestinationStreet(route);

		// Get available space in the destination street
		int free_space = dest_street->getFreeSpace();

		if (m_street->isGreenLight() &&
			vehicle->getRemTime() <= sim_clock &&
			vehicle->getLength() + 3 <= free_space) {

			// Remove vehicle from this street
			m_street->removeVehicle();
			
			// Log it
			logfile << "\nVehicle left " << m_street->getName()
			        << " at time " << sim_clock
				    << " towards " << dest_street->getName();

			// Compute how much time will it take for the vehicle to cross the
			// street. Also, this is the exact time needed for the second
			// vehicle on this street to be just under the traffic lights

			double speed_mps = m_street->getSpeed() / 3.6;
			int tmp_time = (int) ceil((vehicle->getLength() + 3) / speed_mps);

			// Create an event to remove the next vehicle on this street
			events->adicionaEmOrdem(new RemoveVehicleEvent(tmp_time, m_street));

			// Create an event to add the vehicle to destination street
			// We're not taking into account the time it takes for the vehicle
			// to cross the intersection. Teleportation ftw, folks!
			events->adicionaEmOrdem(new AddVehicleEvent(tmp_time, dest_street, vehicle));
		}
	}
}