#include "Street.h"

Street::Street(std::string name, int period, int period_var, int speed,
               int length, bool source, bool drain)
   : m_name(name), m_period(period), m_period_var(period_var),
     m_speed(speed), m_length(length), m_source(source), m_drain(drain),
	 m_filled_space(0) {
}

Street::~Street() {}

bool Street::addVehicle(Vehicle* v) {
    int tmp_space = m_filled_space;
    
	// The actual vehicle size is its nominal size
	// plus some clearance to other vehicles (3 meters)
	tmp_space = tmp_space + v->getLength() + 3;

    // Check if the vehicles fits into the street
    if (tmp_space <= m_length) {
        // Okay, add the vehicle and increment the
		// total used up space
		FilaEnc<Vehicle>::inclui(*v);
		m_filled_space = tmp_space;
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
    return m_period_var;
}

int Street::getSpeed() {
    return m_speed;
}

int Street::getLength() {
    return m_length;
}

bool Street::isSource() {
    return m_source;
}

bool Street::isDrain() {
    return m_drain;
}

void Street::setEfferents(Street* eff) {
    m_efferents = eff;
}

void Street::setEfferents(Street* eff_prob[10]) {
    int i;
    for (i = 0; i < 10; i++) {
        m_eff_prob[i] = eff_prob[i];
    }
}
