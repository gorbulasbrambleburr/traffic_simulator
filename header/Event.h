#ifndef EVENT_H
#define EVENT_H

// Forward declaration
class Street;
class EventList;

class Event {
public:
    Event();
    Event(const int &time, Street* street, EventList* events);
    ~Event();
    virtual void makeItHappen() = 0;
    int getTime();

protected:
	int m_time;           //< Time at which to fire the event.
    Street* m_street;     //< The street which generated the event.
	EventList* m_events;  //< Pointer to the list of future events.
};

#endif // EVENT_H
