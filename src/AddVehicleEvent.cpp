#include "global_variables.h"
#include "function_rand.h"
#include "EventList.h"
#include "AddVehicleEvent.h"
#include "RemoveVehicleEvent.h"
#include "Vehicle.h"
#include "Street.h"

#define MIN_VEHICLE_LENGTH 2
#define MAX_VEHICLE_LENGTH 10
#define MIN_ROUTE 0
#define MAX_ROUTE 9

AddVehicleEvent::AddVehicleEvent(const int &time, Street *street, EventList* events)
    : Event(time, street, events) {
}

AddVehicleEvent::~AddVehicleEvent() {
}

void AddVehicleEvent::makeItHappen() {

    static int vehicle_id = 1;
	
	int vehicle_length = function_rand(MIN_VEHICLE_LENGTH, MAX_VEHICLE_LENGTH);
	
	// Check for available space
	if (vehicle_length + 3 <= m_street->getFreeSpace())
	{
		// Give it a random route to follow
		int vehicle_route = function_rand(MIN_ROUTE,MAX_ROUTE);
		
		// Create it
		Vehicle* vehicle = new Vehicle(vehicle_length, vehicle_route, vehicle_id);

		if (vehicle)
		{
			// The distance this vehicle has to travel		
			int travel_distance = m_street->getLength() - vehicle->getLength() - 3;

			// Expected removal time for this vehicle
			double speed_mps = m_street->getSpeed() / 3.6;
			const int rem_time = sim_clock +  (int) ceil(travel_distance / speed_mps);
			vehicle->setRemTime(rem_time);

			// Add the vehicle to this street
			m_street->addVehicle(vehicle);
		}		
	}

	// Update the next vehicle id
	vehicle_id++;
}

