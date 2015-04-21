#ifndef EVENT_H
#define EVENT_H

// Forward declaration
class Street;

class Event
{
 public:
    Event();
    Event(const int &time, Street* street);
    ~Event();
    virtual void makeItHappen() = 0;

    int getTime() {
       return m_time;
    }

 protected:
    int m_time;        //< Time at which to fire the event.
    Street *m_street;  //< The street which generated the event.
};

#endif // EVENT_H
