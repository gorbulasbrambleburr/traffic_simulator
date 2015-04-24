#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>  // System("pause")

#include "global_variables.h"
#include "ListaEnc.hpp"
#include "Event.h"
#include "EventList.h"
#include "AddVehicleEvent.h"
#include "ChangeLightsEvent.h"
#include "Street.h"
#include "function_rand.h"


#define INPUT_FILENAME "./datafile.in"
#define OUTPUT_FILENAME "./log.res"
#define MIN_VEHICLE_LENGTH 2
#define MAX_VEHICLE_LENGTH 6
#define N_STREETS 14


// Gloabal variables
std::ofstream logfile;     //< Output file to log results.
int sim_clock;             //< Current simulation time in seconds.



///////////////////////////////////////////////////////////////////////////////
///
///
/// \param
/// \return
/// \sa
///////////////////////////////////////////////////////////////////////////////
void open_logfile() {
    logfile.open(OUTPUT_FILENAME);
    if (!logfile.is_open()) {
        std::cout << "Could not open file " << OUTPUT_FILENAME;
    }
}


///////////////////////////////////////////////////////////////////////////////
///
///
/// \param
/// \return
/// \sa
///////////////////////////////////////////////////////////////////////////////
void close_logfile() {
    if (logfile.is_open()) {
        logfile.close();
        std::cout << "Output file closed.";
    }
}



///////////////////////////////////////////////////////////////////////////////
///
///
/// \param
/// \return
/// \sa
///////////////////////////////////////////////////////////////////////////////
void init_traffic_light_events(
	Street* s[N_STREETS], const int &max_time, EventList* events)
{
	// Time of event
	int tmp_time = s[0]->getCrossingPeriod();

	// Create all the fixed events
	while (tmp_time < max_time) {
		
		// O1LESTE & C1LESTE -------------------------------------------
		// Green light
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[0], events));
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[12], events));
		// Update time
		tmp_time = tmp_time + s[0]->getCrossingPeriod();
		// Red light
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[0], events));
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[12], events));

		
		// N1SUL & N2SUL -----------------------------------------------
		// Green light
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[4], events));
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[5], events));
		// Update time
		tmp_time = tmp_time + s[4]->getCrossingPeriod();
		// Red light
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[4], events));
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[5], events));

		// L1OESTE & C1OESTE -------------------------------------------
		// Green light
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[3], events));
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[13], events));
		// Update time
		tmp_time = tmp_time + s[3]->getCrossingPeriod();
		// Red light
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[3], events));
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[13], events));

		// S1NORTE & S2NORTE -------------------------------------------
		// Green light
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[1], events));
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[2], events));
		// Update time
		tmp_time = tmp_time + s[1]->getCrossingPeriod();		
		// Red light
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[1], events));
		events->sorted_insert(new ChangeLightsEvent(tmp_time, s[2], events));
	}
}


///////////////////////////////////////////////////////////////////////////////
///
///
/// \param
/// \return
/// \sa
///////////////////////////////////////////////////////////////////////////////
void init_vehicle_events(Street* s[N_STREETS], const int &max_time, EventList* events)
{
	int i;
    int tmp_time;  // Time of event
    int l_bound;   // Lower bound
	int u_bound;   // Upper bound
    Street* tmp_street;
	Vehicle* tmp_vehicle;

    // Iterate through all the source streets
    for (i = 0; i < 6; i++) {

        tmp_time = 0;
        tmp_street = s[i];

        // Lower and upper bounds of random number.
        l_bound = tmp_street->getPeriod() - tmp_street->getPeriodVar();
        u_bound = tmp_street->getPeriod() + tmp_street->getPeriodVar();

        // Create all the fixed events
        while (tmp_time < max_time) {

            // Actual time of event
            tmp_time = tmp_time + function_rand(l_bound, u_bound);            

			// Create a new random vehicle
			tmp_vehicle = new Vehicle(
				function_rand(MIN_VEHICLE_LENGTH, MAX_VEHICLE_LENGTH),
				function_rand(0,9));

			if (tmp_vehicle) {

				// Add event to the future event list
				events->sorted_insert(new AddVehicleEvent(tmp_time, tmp_street, events, tmp_vehicle));

				// Log it.
				logfile << "\nAddVehicleEvent: " << tmp_street->getName()
						<< " at " << tmp_time;
			}
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
///
///
/// \param
/// \return
/// \sa
///////////////////////////////////////////////////////////////////////////////
void link_streets(Street* s[N_STREETS]) {

    int i;
    Street* eff[10];

    // O1LESTE
    for (i = 0; i < 8; i++) {
        eff[i] = s[12];        // C1LESTE (80%)
    }
    eff[8] = s[10];            // N1NORTE (10%)
    eff[9] = s[6];             // S1SUL (10%)
    s[0]->setEfferents(eff);


    // S1NORTE
    for (i = 0; i < 8; i++) {
        eff[i] = s[12];        // C1LESTE (80%)
    }
    eff[8] = s[10];            // N1NORTE (10%)
    eff[9] = s[11];            // O1OESTE (10%)
    s[1]->setEfferents(eff);


    // S2NORTE
    for (i = 0; i < 3; i++) {
        eff[i] = s[7];         // S2SUL (30%)
    }
    for (i = 3; i < 6; i++) {
        eff[i] = s[13];        // C1OESTE (30%)
    }
    for (i = 6; i < 10; i++) {
        eff[i] = s[8];        // L1LESTE (40%)
    }
    s[2]->setEfferents(eff);


    // L1OESTE
    for (i = 0; i < 3; i++) {
        eff[i] = s[7];         // S2SUL (30%)
    }
    for (i = 3; i < 6; i++) {
        eff[i] = s[12];        // C1LESTE (30%)
    }
    for (i = 6; i < 10; i++) {
        eff[i] = s[8];        // N2NORTE (40%)
    }
    s[3]->setEfferents(eff);


    // N2SUL
    for (i = 0; i < 3; i++) {
        eff[i] = s[7];         // S2SUL (30%)
    }
    for (i = 3; i < 6; i++) {
        eff[i] = s[13];        // C1OESTE (30%)
    }
    for (i = 6; i < 10; i++) {
        eff[i] = s[8];        // L1LESTE (40%)
    }
    s[4]->setEfferents(eff);


    // N1SUL
    for (i = 0; i < 8; i++) {
        eff[i] = s[12];        // C1LESTE (80%)
    }
    eff[8] = s[0];             // O1OESTE (10%)
    eff[9] = s[6];             // S1SUL (10%)
    s[5]->setEfferents(eff);


    // C1LESTE
    for (i = 0; i < 3; i++) {
        eff[i] = s[7];         // S2SUL (30%)
    }
    for (i = 3; i < 6; i++) {
        eff[i] = s[9];        // N2NORTE (30%)
    }
    for (i = 6; i < 10; i++) {
        eff[i] = s[8];        // L1LESTE (40%)
    }
    s[12]->setEfferents(eff);


    // C1OESTE
    for (i = 0; i < 3; i++) {
        eff[i] = s[6];         // S1SUL (30%)
    }
    for (i = 3; i < 6; i++) {
        eff[i] = s[10];        // N1NORTE (30%)
    }
    for (i = 6; i < 10; i++) {
        eff[i] = s[11];        // O1OESTE (40%)
    }
    s[13]->setEfferents(eff);
}


///////////////////////////////////////////////////////////////////////////////
///
///
/// \param
/// \return
/// \sa
///////////////////////////////////////////////////////////////////////////////
void create_streets(Street* s[N_STREETS]) {

	// THIS WILL BE REMOVED ----------------------------------------------------
	int crossing_period = 30;
	// THIS WILL BE REMOVED ----------------------------------------------------

    // Sources
    s[0] = new Street("O1LESTE", 10,  2, 80, 2000, crossing_period, true, false);
    s[1] = new Street("S1NORTE", 30,  7, 60,  500, crossing_period, true, false);
    s[2] = new Street("S2NORTE", 60, 15, 40,  500, crossing_period, true, false);
    s[3] = new Street("L1OESTE", 10,  2, 30,  400, crossing_period, true, false);
    s[4] = new Street(  "N2SUL", 20,  5, 40,  500, crossing_period, true, false);
    s[5] = new Street(  "N1SUL", 20,  5, 60,  500, crossing_period, true, false);

    // Drains
    s[6]  = new Street(  "S1SUL", 0, 0, 60,  500, crossing_period, false, true);
    s[7]  = new Street(  "S2SUL", 0, 0, 40,  500, crossing_period, false, true);
    s[8]  = new Street("L1LESTE", 0, 0, 30,  400, crossing_period, false, true);
    s[9]  = new Street("N2NORTE", 0, 0, 40,  500, crossing_period, false, true);
    s[10] = new Street("N1NORTE", 0, 0, 60,  500, crossing_period, false, true);
    s[11] = new Street("O1OESTE", 0, 0, 80, 2000, crossing_period, false, true);

    // Neuters
    s[12] = new Street("C1LESTE", 0, 0, 60,  300, crossing_period, false, false);
    s[13] = new Street("C1OESTE", 0, 0, 60,  300, crossing_period, false, false);

    logfile << "Streets created.\n";
}



///////////////////////////////////////////////////////////////////////////////
///
///
/// \param
/// \return
/// \sa
///////////////////////////////////////////////////////////////////////////////
void get_simulation_parameters(int& max_time, int& stoplight_period)
{
	std::cout << "\nEnter the total amount of time in hours to simulate the events: ";
	std::cin >> max_time;
	max_time = max_time * 3600;  // Hours -> seconds.

	std::cout << "\nEnter the stoplight period in seconds: ";
	std::cin >> stoplight_period;
}





// ==============================================================================
// ==== MAIN
// ==============================================================================
int main()
{
    
	// Simulation parameters
	int max_time;                //< Maximum simulation time in seconds.
	int stoplight_period;        //< Amount of time the stoplight is green.

    // Events-related variables
    Event *cur_event;            //< Current event being processed.
	EventList *events;           //< Pointer to future event list.

    Street* streets[N_STREETS];  //< Array of Street pointers (constant size).

	// Statistical variables
	int n_events;                //< Number of events.
	int n_inVehicles;            //< Number of vehicles that entered the system.
	int n_outVehicles;           //< Numeber of vehicles that left the system.

    
	




    // --------------------------------------------------------------------------
    // STATE VARIABLES INITIALIZATION
    // --------------------------------------------------------------------------

    sim_clock = 0;  // Global.
    n_events = 0;
	
	// Get simulation time and stoplight period from the console
	get_simulation_parameters(max_time, stoplight_period);
	
	// Create the Future Event List
    events = new EventList();

    // Open output file
    open_logfile();

    // Read the input file and create the streets accordingly
    create_streets(streets);

    // Set all the relations among the streets. This includes all efferent
	// streets of a given street, i.e., a probability vector to determine
	// the next street.
    link_streets(streets);

    // Create some initial events
    init_vehicle_events(streets, max_time, events);
	init_traffic_light_events(streets, max_time, events);


	logfile << "\n\nEvent list - empty? " << events->is_empty() << "\n\n";

    // --------------------------------------------------------------------------
    // BEGIN SIMULATOR
    // --------------------------------------------------------------------------
    while (!events->is_empty() && sim_clock < max_time) {

        // Get next event in time
        cur_event = events->pop_front();

        // Update the simulation clock
        sim_clock = cur_event->getTime();
		
		logfile << "\nEvent time: " << sim_clock;

        // Each event will do what it's supposed to do by polymorphism.
        cur_event->makeItHappen();

		// Deallocate event
		delete(cur_event);

        // Update number of events
        n_events++;

    }
    logfile << "\n\nEvent list - empty? " << events->is_empty() << "\n\n";

    // --------------------------------------------------------------------------
    // STATISTICAL REPORT
    // --------------------------------------------------------------------------



	// Deallocate the list of events
	delete events;
	
	// Close the output file
    close_logfile();

    return 0;
}
