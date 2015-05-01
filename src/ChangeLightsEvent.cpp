#include <iostream>
#include "global_variables.h"
#include "EventList.h"
#include "ChangeLightsEvent.h"
#include "RemoveVehicleEvent.h"
#include "Street.h"

ChangeLightsEvent::ChangeLightsEvent(const int &time, Street* street, EventList* events)
	: Event(time, street, events) {
	// Log it.
	logfile << "\nChangeLightsEvent created: " << m_street->getName()
			<< " at " << m_time;
}

ChangeLightsEvent::~ChangeLightsEvent() {
}

void ChangeLightsEvent::makeItHappen() {

	// Switch the traffic light
	m_street->switchGreenLight();
	

	if (m_street->isGreenLight())
	{
		logfile << "\nGreen light on " << m_street->getName();

		// Schedule a new removal at this exact time
		m_events->sorted_insert(new RemoveVehicleEvent(m_time, m_street, m_events));

		logfile << "\nVehicle at traffic light scheduled to be removed.";
	}
	else
	{
		logfile << "\nRed light on " << m_street;
	}
}