#include "Street.h"

Street::Street(std::string name, int period, int period_var, int speed,
               int length, int cross_period, bool source, bool drain)
   : m_name(name), m_period(period), m_periodVar(period_var),
     m_speed(speed), m_length(length), m_freeSpace(length),
	 m_crossingPeriod(cross_period), m_source(source), m_drain(drain),
	 m_greenLight(false)  {
}

Street::~Street() {}

void Street::addVehicle(Vehicle* vehicle) {
	// Add the vehicle
	FilaEnc<Vehicle*>::inclui(vehicle);

	// Decrement the available space
	m_freeSpace = m_freeSpace - vehicle->getLength() - 3;
}


void Street::removeVehicle() {
	// Remove the vehicle
	Vehicle* vehicle = FilaEnc::retira();

	// Increment the available space
	m_freeSpace = m_freeSpace + vehicle->getLength() + 3;
}

Vehicle* Street::peek() {
	return FilaEnc::primeiro();
}



// Getters & setters

std::string Street::getName() {
    return m_name;
}

int Street::getPeriod() {
    return m_period;
}

int Street::getPeriodVar() {
    return m_periodVar;
}

int Street::getSpeed() {
    return m_speed;
}

int Street::getLength() {
    return m_length;
}

int Street::getFreeSpace() {
	return m_freeSpace;
}

int Street::getCrossingPeriod() {
	return m_crossingPeriod;
}

bool Street::isSource() {
    return m_source;
}

bool Street::isDrain() {
    return m_drain;
}

bool Street::isGreenLight() {
	return m_greenLight;
}

void Street::switchGreenLight() {
	m_greenLight ^= true;
}

Street* Street::getDestinationStreet(int& pos) {
	return m_effProb[pos];
}

void Street::setEfferents(Street* eff_prob[10]) {
    int i;
    for (i = 0; i < 10; i++) {
        m_effProb[i] = eff_prob[i];
    }
}
