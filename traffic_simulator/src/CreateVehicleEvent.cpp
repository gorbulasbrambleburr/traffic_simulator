#define MIN_VEHICLE_LENGTH 2
#define MAX_VEHICLE_LENGTH 6

//=====================
// Forward declarations


//=====================
// Includes
#include <cstdlib>
#include "function_rand.h"
#include "CreateVehicleEvent.h"
#include "Vehicle.h"
#include "Street.h"


CreateVehicleEvent::CreateVehicleEvent(const int &time, Street *street)
    : Event(time, street) {}

CreateVehicleEvent::~CreateVehicleEvent() {}

void CreateVehicleEvent::makeItHappen() {

    int length;  // Length of the vehicle in meters.
    int route;   // The route of the car.

    // Generate a random vehicle length [2m,6m]
    length = function_rand(MIN_VEHICLE_LENGTH, MAX_VEHICLE_LENGTH);

    // Create the vehicle
    Vehicle* vehicle = new Vehicle(length);
    if (vehicle) {

        // Insert the vehicle
        if (m_street->addVehicle(vehicle)) {

            // Generate a random vehicle route [0,9]
			vehicle->setRoute(function_rand(0,9));

			// Compute expected removal time for this vehicle
            const int rem_time = sim_clock + m_street->getLength() / m_street->getSpeed();
			vehicle->setRemTime(rem_time);

            // Log vehicle creation
            logfile << "\nNew vehicle added to street " << m_street->getName()
                    << " at time " << sim_clock;
        }
    }


}

