#ifndef POINT_H  // Header guard to prevent multiple inclusions
#define POINT_H

#include "iostream"  // Include for standard input/output operations
using namespace std; // Use the standard namespace

// Point class declaration
class Point
{
    public:
        // Default constructor for the Point class
        Point();

        // Parameterized constructor for the Point class
        Point(int x, int y);

        // Method to get the x-coordinate
        int get_X() const;

        // Method to get the y-coordinate
        int get_Y() const;

        // Method to set the x-coordinate
        void set_X(int);

        // Method to set the y-coordinate
        void set_Y(int);

        // Virtual destructor for the Point class
        virtual ~Point();

        // Overloaded equality operator to compare two Point objects
        bool operator==(const Point& p);

        // Friend function to overload the output stream operator for Point objects
        friend ostream& operator<<(ostream& o, const Point& p);

    protected:
        int x;  // x-coordinate of the point
        int y;  // y-coordinate of the point

    private:
        // No private members in this class
};

#endif // POINT_H  // End of header guard
