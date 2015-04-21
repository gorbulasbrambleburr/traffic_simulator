#include "global_variables.h"
#include "ChangeLightsEvent.h"
#include "RemoveVehicleEvent.h"
#include "Street.h"

ChangeLightsEvent::ChangeLightsEvent(const int &time, Street* street)
	: Event(time, street) {
}

ChangeLightsEvent::~ChangeLightsEvent() {
}

void ChangeLightsEvent::makeItHappen() {

	// Switch the traffic light
	m_street->switchGreenLight();

	if (m_street->isGreenLight()) {

		logfile << "\Green light at time " << m_time;

		// Perhaps the first vehicle on the street couldn't be removed at its
		// removal time, so we have to reschedule its removal. Thus, we create
		// a RemoveVehicleEvent set on the current clock time. It'll be the
		// first event in the future event list.
		events->adicionaEmOrdem(
			new RemoveVehicleEvent(m_time, m_street, &(m_street->primeiro())));

		logfile << "\nVehicle at traffic light scheduled to be removed.";

		//int tmp_time = 0;
		//while (tmp_time < m_street->getCrossingPeriod()) {
		//if (m_street->primeiro().getRemTime() < sim_clock + tmp_time) {
		//}
	}
}