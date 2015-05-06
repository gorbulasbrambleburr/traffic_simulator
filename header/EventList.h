#ifndef EVENTLIST_H
#define EVENTLIST_

class Event;

#include "ListaEnc.hpp"

class EventList : private ListaEnc<Event*> {
public:
	EventList();
	~EventList();
	void sorted_insert(Event* new_event);
	void first_insert(Event* new_event, int& pos);
	void insert_after(Event* new_event, int& pos);
	Event* pop_front();
	bool is_empty();
	int getSize() const;
};

#endif  // EVENTLIST_H
