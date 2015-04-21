#include "Event.h"

Event::Event(const int &time, Street* street)
    : m_time(time), m_street(street) {}

Event::~Event() {}
