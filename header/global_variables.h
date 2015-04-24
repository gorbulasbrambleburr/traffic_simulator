// This header file contains global variables.

#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

class Event;

#include <fstream>
#include "ListaEnc.hpp"

extern std::ofstream logfile;     //< Output file to log results.
extern int sim_clock;             //< Current simulation time in seconds.

#endif // GLOBAL_VARIABLES_H
