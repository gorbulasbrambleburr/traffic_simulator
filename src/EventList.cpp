#include "EventList.h"
#include "Event.h"
#include "global_variables.h"


EventList::EventList() : ListaEnc<Event*>() {
}

EventList::~EventList() {
	ListaEnc<Event*>::destroiLista();
}




///////////////////////////////////////////////////////////////////////////////
/// Inserts a new event pointer in the event list according to the event time.
///
/// \param Event* new_event - a pointer to the new event to be inserted.
///////////////////////////////////////////////////////////////////////////////
void EventList::sorted_insert(Event* new_event) {	
	Elemento<Event*> *new_node;
	
	// Create a new node
	if (!(new_node = new Elemento<Event*>(new_event, nullptr))) {
		throw ERRO_LISTA_CHEIA;
	}
	
	// Empty list or new event should be the first in the list
	if (_head == nullptr || _head->getInfo()->getTime() > new_event->getTime())
	{		
		new_node->setProximo(_head);
		_head = new_node;
	}
	else
	{
		Elemento<Event*>* current = _head;		
		
		// While the next node is not null and its event time is less than
		// the new event time
		while (current->getProximo() != nullptr &&
			   current->getProximo()->getInfo()->getTime() <= new_event->getTime())
		{
			current = current->getProximo();
		}
		// In any case, the new node will always be after the current node		
		new_node->setProximo(current->getProximo());
		current->setProximo(new_node);
	}
	_size++;
}




///////////////////////////////////////////////////////////////////////////////
/// Checks if the list is empty.
///
/// \return true is it's empty.
///////////////////////////////////////////////////////////////////////////////
bool EventList::is_empty() {
	return ListaEnc::listaVazia();
}





///////////////////////////////////////////////////////////////////////////////
/// Removes the first event of the list of events, reducing its size by 1.
/// The method ListaEnc<Event*>::retiraDoInicio() throws the ERRO_LISTA_VAZIA
/// exception; however, pop_front() is called from inside a loop, which checks
/// for empty list of events.
///
/// \return Event* the pointer to the first Event in the list.
///////////////////////////////////////////////////////////////////////////////
Event* EventList::pop_front() {
	return ListaEnc<Event*>::retiraDoInicio();
}

int EventList::getSize() const {
	return _size;
}