#include "global_variables.h"
#include "EventList.h"
#include "ChangeLightsEvent.h"
#include "RemoveVehicleEvent.h"
#include "Street.h"

ChangeLightsEvent::ChangeLightsEvent(const int &time, Street* street, EventList* events)
	: Event(time, street, events) {
}

ChangeLightsEvent::~ChangeLightsEvent() {
}

void ChangeLightsEvent::makeItHappen() {

	// Switch the traffic light
	m_street->switchGreenLight();
	

	if (m_street->isGreenLight())
	{
		logfile << "\nGreen light on the street " << m_street
			    << "at time " << m_time;

		// Perhaps the first vehicle on the street couldn't be removed at its
		// removal time, so we have to reschedule its removal. Thus, we create
		// a RemoveVehicleEvent set on the current clock time. It'll be the
		// first event in the future event list.
		m_events->sorted_insert(new RemoveVehicleEvent(m_time, m_street, m_events));

		logfile << "\nVehicle at traffic light scheduled to be removed.";
	}
	else
	{
		logfile << "\nRed light on the street " << m_street
			    << "at time " << m_time;
	}
}