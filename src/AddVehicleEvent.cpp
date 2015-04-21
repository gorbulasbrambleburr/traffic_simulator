#include <cstdlib>
#include "global_variables.h"
#include "function_rand.h"
#include "AddVehicleEvent.h"
#include "RemoveVehicleEvent.h"
#include "Vehicle.h"
#include "Street.h"


AddVehicleEvent::AddVehicleEvent(const int &time, Street *street, Vehicle* vehicle)
    : Event(time, street), m_vehicle(vehicle) {
}

AddVehicleEvent::~AddVehicleEvent() {
}

void AddVehicleEvent::makeItHappen() {

    // Insert the vehicle on the street
    if (m_street->addVehicle(m_vehicle)) {

		// The distance this vehicle has to travel		
		int travel_distance = m_street->getLength() - m_vehicle->getLength() - 3;

		// Expected removal time for this vehicle
		const int rem_time = sim_clock +  travel_distance / m_street->getSpeed();
		m_vehicle->setRemTime(rem_time);

		// Log vehicle insertion
        logfile << "\nNew vehicle added to street " << m_street->getName()
                << " at time " << sim_clock;

		// Add a new scheduled event to remove the vehicle
		events->adicionaEmOrdem(
			new RemoveVehicleEvent(rem_time, m_street, m_vehicle));

		logfile << "\nVehicle scheduled to be removed at " << rem_time;        
    }
}

