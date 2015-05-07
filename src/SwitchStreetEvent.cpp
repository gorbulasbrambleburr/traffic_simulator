#include "global_variables.h"
#include "EventList.h"
#include "SwitchStreetEvent.h"
#include "RemoveVehicleEvent.h"
#include "Vehicle.h"
#include "Street.h"
#include "function_rand.h"

#define MIN_ROUTE 0
#define MAX_ROUTE 9

SwitchStreetEvent::SwitchStreetEvent(const int &time, Street *street, EventList* events, Vehicle* vehicle)
    : Event(time, street, events), m_vehicle(vehicle) {
}

SwitchStreetEvent::~SwitchStreetEvent() {
}

void SwitchStreetEvent::makeItHappen() {
	
	// The distance this vehicle has to travel
	int travel_distance = m_street->getLength() - m_vehicle->getLength() - 3;

	// Expected removal time for this vehicle
	double speed_mps = m_street->getSpeed() / 3.6;
	const int rem_time = sim_clock +  (int) ceil(travel_distance / speed_mps);
	m_vehicle->setRemTime(rem_time);
		
	// Check if it's a drain street (1) or if the street was empty before this
	// vehicle was added (2), then create a new removal event for when it reaches
	// the end of the street (1) / stoplight (2).
	if (m_street->isDrain() || m_street->isEmpty()) {

		// Create an event to remove this vehicle
		m_events->sorted_insert(new RemoveVehicleEvent(rem_time, m_street, m_events));
	}

	// Update the vehicle route
	m_vehicle->setRoute(function_rand(MIN_ROUTE,MAX_ROUTE));

	// Add the vehicle
	m_street->addVehicle(m_vehicle);
}

