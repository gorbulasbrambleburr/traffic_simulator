#include <iostream>
#include <string.h>
#include <cstdlib>

#include "global_variables.h"
#include "ListaEnc.hpp"
#include "Event.h"
#include "CreateVehicleEvent.h"
#include "Street.h"
#include "function_rand.h"


#define INPUT_FILENAME "./datafile.in"
#define OUTPUT_FILENAME "./log.res"
#define N_STREETS 14


//using namespace std;

//=====================
// Gloabal variables
std::ofstream logfile;     //< Output file to log results.
int sim_clock;             //< Current simulation time in seconds.
ListaEnc<Event*> *events;  //< Pointer to future event list.



void open_logfile() {
    logfile.open(OUTPUT_FILENAME);
    if (!logfile.is_open()) {
        std::cout << "Could not open file " << OUTPUT_FILENAME;
    }
}

void close_logfile() {
    if (logfile.is_open()) {
        logfile.close();
        std::cout << "Output file closed.";
    }
}


void create_initial_events(Street* s[N_STREETS], const int &max_time) {
    int i;
//    int counter;
    int tmp_time;
    int l_bound, u_bound;
    Street* tmp_street;

    // Iterate through all the source streets
    for (i = 0; i < 6; i++) {

//        counter = 0;
        tmp_time = 0;
        tmp_street = s[i];

        // Lower and upper bounds of random number.
        l_bound = tmp_street->getPeriod() - tmp_street->getPeriodVar();
        u_bound = tmp_street->getPeriod() + tmp_street->getPeriodVar();

        // Create all the fixed events
        while (tmp_time < max_time) {

            // Actual time of event
            tmp_time = tmp_time + function_rand(l_bound, u_bound);

            // Add event to the future event list
            events->adicionaEmOrdem(new CreateVehicleEvent(tmp_time, tmp_street));

            // Log it.
            logfile << "\nCreateVehicleEvent: " << tmp_street->getName()
                    << " at " << tmp_time;

            // Counter just for fun
//            counter++;
        }
//        logfile << "\nNew " << counter  << " CreateVehicleEvent created at street " << tmp_street->getName();
    }

    //TODO(mak)
}


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



void create_streets(Street* s[N_STREETS]) {

    // Sources
    s[0] = new Street("O1LESTE", 10,  2, 80, 2000, true, false);
    s[1] = new Street("S1NORTE", 30,  7, 60,  500, true, false);
    s[2] = new Street("S2NORTE", 60, 15, 40,  500, true, false);
    s[3] = new Street("L1OESTE", 10,  2, 30,  400, true, false);
    s[4] = new Street(  "N2SUL", 20,  5, 40,  500, true, false);
    s[5] = new Street(  "N1SUL", 20,  5, 60,  500, true, false);

    // Drains
    s[6]  = new Street(  "S1SUL", 0, 0, 60,  500, false, true);
    s[7]  = new Street(  "S2SUL", 0, 0, 40,  500, false, true);
    s[8]  = new Street("L1LESTE", 0, 0, 30,  400, false, true);
    s[9]  = new Street("N2NORTE", 0, 0, 40,  500, false, true);
    s[10] = new Street("N1NORTE", 0, 0, 60,  500, false, true);
    s[11] = new Street("O1OESTE", 0, 0, 80, 2000, false, true);

    // Neuters
    s[12] = new Street("C1LESTE", 0, 0, 60,  300, false, false);
    s[13] = new Street("C1OESTE", 0, 0, 60,  300, false, false);

    logfile << "Streets created.\n";
}


// ==============================================================================
// ==== MAIN
// ==============================================================================
int main(int argc, char *argv[])
{
    // Variables
    int max_time;      //< Maximum simulation time in seconds.
    int n_events;      //< Number of events.
    Event *cur_event;  //< Current event being processed.

    Street* streets[N_STREETS];    //< Array of Street pointers (constant size).
//    ListaEnc<Crossing> crossings;

    // Get simulation time in hours from input parameters
    if (argc != 2) {
        std::cout << "Wrong number of input variables!\n";
        std::cout << "Please enter total simulation time in hours.\n\n";
        return 1;
    }
    max_time = 3600 * atoi(argv[1]);  // Hours -> seconds conversion.



    // --------------------------------------------------------------------------
    // STATE VARIABLES INITIALIZATION
    // --------------------------------------------------------------------------

    sim_clock = 0;
    n_events = 0;
    events = new ListaEnc<Event*>();

    // Open output file
    open_logfile();

    // Read the input file and create the streets accordingly
    create_streets(streets);

    // Set all the relations among the streets.
    // This includes all efferent streets of a given street,
    // as well as a probability vector to determine the next
    // street.
    link_streets(streets);
    // TODO(mak)

    // Create some initial events
    create_initial_events(streets, max_time);
    logfile << "\n\nEvent list - empty? " << events->listaVazia() << "\n\n";

    // --------------------------------------------------------------------------
    // BEGIN SIMULATOR
    // --------------------------------------------------------------------------
    while (!events->listaVazia() && sim_clock < max_time) {

        // Get next event in time
        cur_event = events->retiraDoInicio();

        // Update the simulation clock
        sim_clock = cur_event->getTime();

        logfile << "\nEvent time: " << sim_clock;

        // Perform event
        // Each event will do what it's supposed
        // to do by polymorphism.
        cur_event->makeItHappen();


        // Update other statistics-related stuff
        // TODO(mak)

        // Update number of events
        n_events++;

    }
    logfile << "\n\nEvent list - empty? " << events->listaVazia() << "\n\n";

    // --------------------------------------------------------------------------
    // STATISTICAL REPORT
    // --------------------------------------------------------------------------





    close_logfile();
    return 0;
}
