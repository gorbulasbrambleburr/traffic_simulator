#include <iostream>
#include "global_variables.h"
#include "EventList.h"
#include "ChangeLightsEvent.h"
#include "RemoveVehicleEvent.h"
#include "Street.h"

ChangeLightsEvent::ChangeLightsEvent(
	const int &time, Street* first_street,
	Street* second_street, EventList* events)
		: Event(time, first_street, events), m_secondStreet(second_street) {

	logfile << "\nChangeLightsEvent created: " << m_street->getName()
			<< " at " << m_time;
}

ChangeLightsEvent::~ChangeLightsEvent() {
}

void ChangeLightsEvent::makeItHappen() {

	// Switch the traffic light
	m_street->switchGreenLight();
	m_secondStreet->switchGreenLight();
	
	doSomething(m_street);
	doSomething(m_secondStreet);
	
}

void ChangeLightsEvent::doSomething(Street* s) {
	if (s->isGreenLight())
	{
		logfile << "\nGreen light on " << s->getName();

		// Schedule a new removal at this exact time
		m_events->sorted_insert(new RemoveVehicleEvent(m_time, s, m_events));

		logfile << "\nVehicle at traffic light scheduled to be removed.";
	}
	else
	{
		logfile << "\nRed light on " << s->getName();
		logfile << "\nCurrent inflow: " << s->getInflow();
		logfile << "\nCurrent outflow: " << s->getOutflow();
	}
}