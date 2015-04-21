#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle
{
 public:
    Vehicle(int length, int route);
    ~Vehicle();
    int getLength();
	int getRoute();
	int getRemTime();
	void setRemTime(const int &rem_time);

 private:
    int m_length;   //< The length of the vehicle.
    int m_route;    //< The route to be taken randomly.
	int m_remTime;  //< The vehicle removal time.
};

#endif // VEHICLE_H
