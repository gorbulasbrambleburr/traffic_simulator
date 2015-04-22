#ifndef STREET_H
#define STREET_H

//=====================
// Forward declarations

//=====================
// Includes
#include <string>
#include "FilaEnc.hpp"
#include "Vehicle.h"

class Street : private FilaEnc<Vehicle*>
{
 public:
    Street(std::string name, int period, int p_var, int speed,
           int length, int cross_period, bool source, bool drain);

    ~Street();
    void addVehicle(Vehicle* vehicle);
	void removeVehicle();
	Vehicle* peek();

	// Getters & setters
    std::string getName();
    int getPeriod();
    int getPeriodVar();
    int getSpeed();
    int getLength();
	int getFreeSpace();
	int getCrossingPeriod();
    bool isSource();
    bool isDrain();
	bool isGreenLight();
	void switchGreenLight();
	Street* getDestinationStreet(int& pos);
    void setEfferents(Street* eff_prob[10]);


 private:
    std::string m_name;      //< The name of the street.
    int m_period;            //< Period at which cars are created.
    int m_periodVar;         //< Period variance.
    int m_speed;             //< The constant speed in km/h
    int m_length;            //< The length in meters.
	int m_freeSpace;         //< The available space in meters.
	int m_crossingPeriod;    //< The period on which the traffic light is green.
	bool m_source;           //< Is it a source of vehicles?
    bool m_drain;            //< Is it a drain for vehicles?
	bool m_greenLight;       //< Is the traffic light green?
	Street* m_effProb[10];   //< List of pointers to efferents based on probability.
};
#endif // STREET_H
