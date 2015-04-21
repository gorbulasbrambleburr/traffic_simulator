#ifndef STREET_H
#define STREET_H

//=====================
// Forward declarations

//=====================
// Includes
#include <string>
#include "FilaEnc.hpp"
#include "Vehicle.h"

class Street : private FilaEnc<Vehicle>
{
 public:
    Street(std::string name, int period, int p_var, int speed,
           int length, bool source, bool drain);

    ~Street();
    bool addVehicle(Vehicle* v);
    std::string getName();
    int getPeriod();
    int getPeriodVar();
    int getSpeed();
    int getLength();
    bool isSource();
    bool isDrain();
    void setEfferents(Street* eff);
    void setEfferents(Street* eff_prob[10]);

 private:
    std::string m_name;      //< The name of the street.
    int m_period;            //< Period at which cars are created.
    int m_period_var;        //< Period variance.
    int m_speed;             //< The constant speed in km/h
    int m_length;            //< The length in meters.
    bool m_source;           //< Is it a source of vehicles?
    bool m_drain;            //< Is it a drain for vehicles?
    Street* m_efferents;     //< Pointer to efferent streets.
    Street* m_eff_prob[10];  //< List of pointers to efferents based on probability.
    int m_filled_space;      //< The length of the street currently in use.
};
#endif // STREET_H
