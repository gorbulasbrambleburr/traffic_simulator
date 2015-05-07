#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle
{
 public:
    Vehicle(int length, int route, int id);
    ~Vehicle();
    int getLength();
	int getRoute();
	void setRoute(const int route);
	int getRemTime();
	void setRemTime(const int &rem_time);
	int getID() const;
	void setID(int id);

 private:
    int m_length;   //< The length of the vehicle.
    int m_route;    //< The route to be taken randomly.
	int m_remTime;  //< The vehicle removal time.
	int m_id;       //< A unique number for this vehicle.
};

#endif // VEHICLE_H
