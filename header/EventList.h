#ifndef EVENTLIST_H
#define EVENTLIST_

class Event;

#include "ListaEnc.hpp"

class EventList : private ListaEnc<Event*> {
public:
	EventList();
	~EventList();
	void sorted_insert(Event* event);
	Event* pop_front();
	bool is_empty();
	int getSize() const;
	
	//bool operator> (const Event* event) const;
};

#endif  // EVENTLIST_H
