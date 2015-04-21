#include "Vehicle.h"

Vehicle::Vehicle(int length, int route)
    : m_length(length) {}

Vehicle::~Vehicle() {}

int Vehicle::getLength() {
    return m_length;
}

int Vehicle::getRoute() {
	return m_route;
}

int Vehicle::getRemTime() {
	return m_remTime;
}

void Vehicle::setRemTime(const int &rem_time) {
	m_remTime = rem_time;
}