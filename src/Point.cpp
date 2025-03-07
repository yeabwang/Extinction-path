#include "Point.h"

Point::Point()
{
    x = 0;
    y = 0;
}


Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point::~Point()
{
    //dtor
}
int Point::get_X() const
{
    return x;
}
int  Point::get_Y() const
{
    return y;
}
void Point::set_X(int X)
{
    x=X;
}
void Point::set_Y(int Y)
{
    y=Y;
}

bool Point:: operator==(const Point& p)
{
    if(this->x==p.x && this->y == p.y)
        return true;

    return false;
}


ostream& operator<<(ostream& o,const Point& p)
{

    o<<endl;
    o<<"X: "<< p.get_X()<<endl;
    o<<"Y: "<< p.get_Y()<<endl;
    return o;
}
