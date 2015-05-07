#include "Vehicle.h"

Vehicle::Vehicle(int length, int route, int id)
    : m_length(length), m_route(route), m_id(id) {}

Vehicle::~Vehicle() {}

int Vehicle::getLength() {
    return m_length;
}

int Vehicle::getRoute() {
	return m_route;
}

void Vehicle::setRoute(const int route) {
	m_route = route;
}

int Vehicle::getRemTime() {
	return m_remTime;
}

void Vehicle::setRemTime(const int &rem_time) {
	m_remTime = rem_time;
}

int Vehicle::getID() const {
	return m_id;
}

void Vehicle::setID(int id) {
	m_id = id;
}