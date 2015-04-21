#ifndef CREATEVEHICLEEVENT_H
#define CREATEVEHICLEEVENT_H

#include "global_variables.h"
#include "Event.h"

class CreateVehicleEvent : public Event {
 public:
     CreateVehicleEvent(const int &time, Street* street);
     ~CreateVehicleEvent();
     void makeItHappen();
};
#endif // CREATEVEHICLEEVENT_H
