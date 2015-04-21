#include "Street.h"

Street::Street(std::string name, int period, int period_var, int speed,
               int length, int cross_period, bool source, bool drain)
   : m_name(name), m_period(period), m_periodVar(period_var),
     m_speed(speed), m_length(length), m_filledSpace(0),
	 m_crossingPeriod(cross_period), m_source(source), m_drain(drain),
	 m_greenLight(false)  {
}

Street::~Street() {}

bool Street::addVehicle(Vehicle* v) {
    int tmp_space = m_filledSpace;
    
	// The actual vehicle size is its nominal size
	// plus some clearance to other vehicles (3 meters)
	tmp_space = tmp_space + v->getLength() + 3;

    // Check if the vehicles fits into the street
    if (tmp_space <= m_length) {
        // Okay, add the vehicle and increment the
		// total used up space
		FilaEnc<Vehicle>::inclui(*v);
		m_filledSpace = tmp_space;
        return true;
    } else {
        // Could not add the vehicle.
		return false;
    }
}

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

void Street::setEfferents(Street* eff_prob[10]) {
    int i;
    for (i = 0; i < 10; i++) {
        m_effProb[i] = eff_prob[i];
    }
}

// Overriden methods
Vehicle Street::primeiro() {
	return FilaEnc::primeiro();
}