#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>  // System("pause")
#include <ctime>

#include "global_variables.h"
#include "ListaEnc.hpp"
#include "Event.h"
#include "EventList.h"
#include "AddVehicleEvent.h"
#include "ChangeLightsEvent.h"
#include "Street.h"
#include "function_rand.h"

#define OUTPUT_FILENAME "./results.log"
#define MIN_VEHICLE_LENGTH 2
#define MAX_VEHICLE_LENGTH 10
#define MIN_ROUTE 0
#define MAX_ROUTE 9
#define N_STREETS 14

// Gloabal variables
std::ofstream logfile;     //< Output file to log results.
int sim_clock;             //< Current simulation time in seconds.



///////////////////////////////////////////////////////////////////////////////
/// Opens the output file OUTPUT_FILENAME.
///
/// \param
/// \return
/// \sa close_logfile
///////////////////////////////////////////////////////////////////////////////
void open_logfile() {
    logfile.open(OUTPUT_FILENAME);
    if (!logfile.is_open()) {
        std::cout << "Could not open file " << OUTPUT_FILENAME;
    }
}


///////////////////////////////////////////////////////////////////////////////
/// Closes the output file.
///
/// \param
/// \return
/// \sa open_logfile
///////////////////////////////////////////////////////////////////////////////
void close_logfile() {
    if (logfile.is_open()) {
        logfile.close();
    }
}


///////////////////////////////////////////////////////////////////////////////
/// Write the statistical report to the output file and the console.
///
/// \param Street* s[N_STREETS] - array of street pointers.
/// \return
/// \sa
///////////////////////////////////////////////////////////////////////////////
void generate_report(Street* s[N_STREETS])
{
	int i;	
	int sum_inflow = 0;
	int sum_outflow = 0;
	
	std::cout << "\n\n";
	logfile << "\n\n";
	//std::cout << "Street   Inflow    Outflow    Current\n";
	std::cout << "Street" << "\t\t"
	          << "In" << "\t"
	          << "Out" << "\t"
	          << "Trapped";
	std::cout << "\n--------------------------------------\n";
	logfile << "Street" << "\t\t"
	        << "In" << "\t"
	        << "Out" << "\t"
	        << "Trapped";
	logfile << "\n--------------------------------------\n";
	for (i = 0; i < N_STREETS; i++)
	{
		std::cout << s[i]->getName() << "\t\t"
			      << s[i]->getInflow() << "\t"
				  << s[i]->getOutflow() << "\t"
				  << s[i]->getInflow() -
				     s[i]->getOutflow()
				  << "\n";
		logfile << s[i]->getName() << "\t\t"
			    << s[i]->getInflow() << "\t"
				<< s[i]->getOutflow() << "\t"
				<< s[i]->getInflow() -
				   s[i]->getOutflow()
				<< "\n";

		sum_inflow = sum_inflow + s[i]->getInflow();
		sum_outflow = sum_outflow + s[i]->getOutflow();
	}
	std::cout << "\n\n";
	std::cout << "\nNumber of vehicles that entered the system: " << sum_inflow;
	std::cout << "\nNumber of vehicles that left the system...: " << sum_outflow;
	std::cout << "\nNumber of vehicles trapped in the system..: " << sum_inflow - sum_outflow;
	logfile << "\n\n";
	logfile << "\nNumber of vehicles that entered the system: " << sum_inflow;
	logfile << "\nNumber of vehicles that left the system...: " << sum_outflow;
	logfile << "\nNumber of vehicles trapped in the system..: " << sum_inflow - sum_outflow;
}


///////////////////////////////////////////////////////////////////////////////
/// Creates all the lights changing events to be used in the simulation.
///
/// \param Street* s[N_STREETS] - array of street pointers.
/// \param const int &max_time  - reference to the total simulation time.
/// \param EventList* events    - pointer to list of future events.
/// \return
/// \sa
///////////////////////////////////////////////////////////////////////////////
void init_traffic_light_events(
	Street* s[N_STREETS],       // List of street pointers
	const int &max_time,        // Maximum simulation time
	EventList* events,          // Pointer to list of future events
	int& stoplight_period)      // Stoplight period (equal in all streets)
{
	std::cout << "\nCreating traffic light events...";
	int pos;
	
	// Time of event
	int tmp_time = stoplight_period;

	// Pointers to streets
	Street *s0, *s1, *s2, *s3, *s4, *s5, *s12, *s13;
	s0 = s[0]; s1 = s[1]; s2  = s[2];  s3  = s[3];
	s4 = s[4]; s5 = s[5]; s12 = s[12]; s13 = s[13];

	// Create the first event
	events->first_insert(new ChangeLightsEvent(tmp_time, s0, s12, events), pos);

	// Create all the fixed events
	while (tmp_time < max_time) {
		
		// O1LESTE & C1LESTE -------------------------------------------
		// Update time
		tmp_time = tmp_time + stoplight_period;
		// Red light
		events->insert_after(new ChangeLightsEvent(tmp_time, s0, s12, events), pos);

		
		// N1SUL & N2SUL -----------------------------------------------
		// Green light
		events->insert_after(new ChangeLightsEvent(tmp_time, s4, s5, events), pos);
		// Update time
		tmp_time = tmp_time + stoplight_period;
		// Red light
		events->insert_after(new ChangeLightsEvent(tmp_time, s4, s5, events), pos);

		// L1OESTE & C1OESTE -------------------------------------------
		// Green light
		events->insert_after(new ChangeLightsEvent(tmp_time, s3, s13, events), pos);
		// Update time
		tmp_time = tmp_time + stoplight_period;
		// Red light
		events->insert_after(new ChangeLightsEvent(tmp_time, s3, s13, events), pos);

		// S1NORTE & S2NORTE -------------------------------------------
		// Green light
		events->insert_after(new ChangeLightsEvent(tmp_time, s1, s2, events), pos);
		// Update time
		tmp_time = tmp_time + stoplight_period;		
		// Red light
		events->insert_after(new ChangeLightsEvent(tmp_time, s1, s2, events), pos);

		// O1LESTE & C1LESTE -------------------------------------------
		// Green light
		events->insert_after(new ChangeLightsEvent(tmp_time, s0, s12, events), pos);
	}
	std::cout << " done.";
}


///////////////////////////////////////////////////////////////////////////////
/// Creates all the initial vehicles insertion events. There will be more
/// vehicles insertion events happening during the simulation every time a
/// vehicle leaves a street towards another.
///
/// \param Street* s[N_STREETS] - array of street pointers.
/// \param const int &max_time  - reference to the total simulation time.
/// \param EventList* events    - pointer to list of future events.
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

	std::cout << "\nGenerating initial vehicle events...";

    // Iterate through all the source streets
    for (i = 0; i < 6; i++) {

        int pos;
		tmp_time = 0;
        tmp_street = s[i];

        // Lower and upper bounds of random number.
        l_bound = tmp_street->getPeriod() - tmp_street->getPeriodVar();
        u_bound = tmp_street->getPeriod() + tmp_street->getPeriodVar();

        
		// Insert first vehicle event
		// --------------------------

		// Actual time of event
        tmp_time = tmp_time + function_rand(l_bound, u_bound);            

		// Create a new random vehicle
		tmp_vehicle = new Vehicle(
			function_rand(MIN_VEHICLE_LENGTH, MAX_VEHICLE_LENGTH),  // length
			function_rand(MIN_ROUTE,MAX_ROUTE),  // route
			-1);                 // vehicle id

		if (tmp_vehicle) {

			// Add event to the future event list
			events->first_insert(new AddVehicleEvent(tmp_time, tmp_street, events, tmp_vehicle), pos);

			// Log it.
			logfile << "\nAddVehicleEvent: " << tmp_street->getName()
					<< " at " << tmp_time;
		}
		
		
		// Create all other vehicles
		// -------------------------
        while (tmp_time < max_time) {

            // Actual time of event
            tmp_time = tmp_time + function_rand(l_bound, u_bound);            

			// Create a new random vehicle
			tmp_vehicle = new Vehicle(
				function_rand(MIN_VEHICLE_LENGTH, MAX_VEHICLE_LENGTH),  // length
				function_rand(MIN_ROUTE,MAX_ROUTE),  // route
				-1);                 // vehicle id

			if (tmp_vehicle) {

				// Add event to the future event list
				events->insert_after(new AddVehicleEvent(tmp_time, tmp_street, events, tmp_vehicle), pos);

				// Log it.
				logfile << "\nAddVehicleEvent: " << tmp_street->getName()
						<< " at " << tmp_time;
			}
        }
    }
	std::cout << " done.";
}



///////////////////////////////////////////////////////////////////////////////
/// Links source/intermediary streets to intermediary/drain ones.
///
/// \param Street* s[N_STREETS] - array of street pointers.
/// \return
/// \sa create_streets
///////////////////////////////////////////////////////////////////////////////
void link_streets(Street* s[N_STREETS]) {

    int i;
    Street* eff[10];

	std::cout << "\nLinking streets...";

    // O1LESTE
    for (i = 0; i < 8; i++) {
        eff[i] = s[12];        // C1LESTE (80%)
    }
    eff[8] = s[11];            // N1NORTE (10%)
    eff[9] = s[7];             // S1SUL (10%)
    s[0]->setEfferents(eff);


    // S1NORTE
    for (i = 0; i < 8; i++) {
        eff[i] = s[12];        // C1LESTE (80%)
    }
    eff[8] = s[11];            // N1NORTE (10%)
    eff[9] = s[6];             // O1OESTE (10%)
    s[1]->setEfferents(eff);


    // S2NORTE
    for (i = 0; i < 3; i++) {
        eff[i] = s[10];        // N2NORTE (30%) -- Originally S2SUL!
    }
    for (i = 3; i < 6; i++) {
        eff[i] = s[13];        // C1OESTE (30%)
    }
    for (i = 6; i < 10; i++) {
        eff[i] = s[9];         // L1LESTE (40%)
    }
    s[2]->setEfferents(eff);


    // L1OESTE
    for (i = 0; i < 3; i++) {
        eff[i] = s[8];         // S2SUL (30%)
    }
    for (i = 3; i < 6; i++) {
        eff[i] = s[13];        // C1OESTE (30%) -- Originally C1LESTE!
    }
    for (i = 6; i < 10; i++) {
        eff[i] = s[10];        // N2NORTE (40%)
    }
    s[3]->setEfferents(eff);


    // N2SUL
    for (i = 0; i < 3; i++) {
        eff[i] = s[8];         // S2SUL (30%)
    }
    for (i = 3; i < 6; i++) {
        eff[i] = s[13];        // C1OESTE (30%)
    }
    for (i = 6; i < 10; i++) {
        eff[i] = s[9];        // L1LESTE (40%)
    }
    s[4]->setEfferents(eff);


    // N1SUL
    for (i = 0; i < 8; i++) {
        eff[i] = s[12];       // C1LESTE (80%)
    }
    eff[8] = s[6];            // O1OESTE (10%)
    eff[9] = s[7];            // S1SUL (10%)
    s[5]->setEfferents(eff);


    // C1LESTE
    for (i = 0; i < 3; i++) {
        eff[i] = s[8];         // S2SUL (30%)
    }
    for (i = 3; i < 6; i++) {
        eff[i] = s[10];        // N2NORTE (30%)
    }
    for (i = 6; i < 10; i++) {
        eff[i] = s[9];         // L1LESTE (40%)
    }
    s[12]->setEfferents(eff);


    // C1OESTE
    for (i = 0; i < 3; i++) {
        eff[i] = s[7];         // S1SUL (30%)
    }
    for (i = 3; i < 6; i++) {
        eff[i] = s[11];        // N1NORTE (30%)
    }
    for (i = 6; i < 10; i++) {
        eff[i] = s[6];         // O1OESTE (40%) 
    }
    s[13]->setEfferents(eff);

	std::cout << " done.";
}


///////////////////////////////////////////////////////////////////////////////
/// Create all the streets used in the simulation.
///
/// \param Street* s[N_STREETS]  - array of street pointers.
/// \param int &stoplight_period - the period at which the stoplights will be
///        turned on.
/// \return
/// \sa link_streets
///////////////////////////////////////////////////////////////////////////////
void create_streets(Street* s[N_STREETS]) {

	std::cout << "\nCreating streets...";

    // Sources
    s[0] = new Street("O1LESTE", 10,  2, 80, 2000, false);
    s[1] = new Street("S1NORTE", 30,  7, 60,  500, false);
    s[2] = new Street("S2NORTE", 60, 15, 40,  500, false);
    s[3] = new Street("L1OESTE", 10,  2, 30,  400, false);
    s[4] = new Street(  "N2SUL", 20,  5, 40,  500, false);
    s[5] = new Street(  "N1SUL", 20,  5, 60,  500, false);
                                                   
    // Drains                                      
    s[6]  = new Street("O1OESTE", 0, 0, 80, 2000, true);
	s[7]  = new Street(  "S1SUL", 0, 0, 60,  500, true);
    s[8]  = new Street(  "S2SUL", 0, 0, 40,  500, true);
    s[9]  = new Street("L1LESTE", 0, 0, 30,  400, true);
    s[10] = new Street("N2NORTE", 0, 0, 40,  500, true);
    s[11] = new Street("N1NORTE", 0, 0, 60,  500, true);    
                                                  
    // Neuters                                    
    s[12] = new Street("C1LESTE", 0, 0, 60,  300, false);
    s[13] = new Street("C1OESTE", 0, 0, 60,  300, false);

    std::cout << " done.";
}



///////////////////////////////////////////////////////////////////////////////
/// Gets the total simulation time and the stoplight period from the console.
///
/// \param const int &max_time   - reference to the total simulation time.
/// \param int &stoplight_period - the period at which the stoplights will be
///        turned on.
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
    // Set up a clock to measure the real simulation time
	clock_t begin = std::clock();
	
	// Simulation parameters
	int max_time;                //< Maximum simulation time in seconds.
	int stoplight_period;        //< Amount of time the stoplight is green.

    // Events-related variables
    Event *cur_event;            //< Current event being processed.
	EventList *events;           //< Pointer to future event list.

    Street* streets[N_STREETS];  //< Array of Street pointers (constant size).

	// Statistical variables
	int n_events;                //< Number of events.	
	
	// Initialize seed
    srand((unsigned)time(NULL));



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
	init_traffic_light_events(streets, max_time, events, stoplight_period);

	

    // --------------------------------------------------------------------------
    // BEGIN SIMULATOR
    // --------------------------------------------------------------------------
    
	logfile << "\n\nStarting simulation...\n";
	std::cout << "\n\nRunning simulation...";
	
	while (!events->is_empty() && sim_clock < max_time) {

		// Update number of events
        n_events++;
		
		// Get next event in time
        cur_event = events->pop_front();

        // Update the simulation clock
        sim_clock = cur_event->getTime();
		
		logfile << "\n\n-------------------------------------------------";
		logfile << "\nEvent " << n_events << " of " << events->getSize();
		logfile << "\nEvent time: " << sim_clock;
		//logfile << "\nList size...: " << events->getSize();		
		//std::cout << "\nEvent number: " << n_events;
		//std::cout << "\nEvent time..: " << sim_clock;
		//std::cout << "\nList size: " << events->getSize();

        // Each event will do what it's supposed to do by polymorphism.
        cur_event->makeItHappen();

		// Deallocate event
		delete(cur_event);
    }

    std::cout << " finished.";

	// --------------------------------------------------------------------------
    // STATISTICAL REPORT
    // --------------------------------------------------------------------------

	generate_report(streets);
	

	// Deallocate the list of events
	delete events;
	
	// Close the output file
    close_logfile();

	
	std::cout << "\n\nCheck output file ('"<< OUTPUT_FILENAME <<"') for logging information.\n";

	// Stop the clock
	clock_t end = std::clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "\n\nTotal running time: " << elapsed_secs << "\n\n";

	system("pause");
    return 0;
}
