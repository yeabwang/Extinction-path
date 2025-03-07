#ifndef POINT_H
#define POINT_H
#include "iostream"
using namespace std;



class Point
{
    public:
        Point();
        Point(int x,int y);
        int get_X() const;
        int get_Y() const;
        void set_X(int);
        void set_Y(int);
        virtual ~Point();
        bool operator==(const Point& p);
        friend ostream& operator<<(ostream& o,const Point& p);
    protected:
        int x;
        int y;
    private:
};





#endif // POINT_H
