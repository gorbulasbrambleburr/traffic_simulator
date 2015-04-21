#include "Vehicle.h"

Vehicle::Vehicle(int length)
    : m_length(length) {}

Vehicle::~Vehicle() {}

int Vehicle::getLength() {
    return m_length;
}

void Vehicle::setRoute(const int &route) {
	m_route = route;
}
	
void Vehicle::setRemTime(const int &rem_time) {
	m_remTime = rem_time;
}