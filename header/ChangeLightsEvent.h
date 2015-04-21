#ifndef CHANGELIGHTSEVENT_H
#define CHANGELIGHTSEVENT_H

#include "global_variables.h"
#include "Event.h"

class ChangeLightsEvent : public Event {
 public:
    ChangeLightsEvent(const int &time, Street* street);
    ~ChangeLightsEvent();
    void makeItHappen();
};
#endif // CHANGELIGHTSEVENT_H
