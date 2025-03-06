#include "Point.h"  // Include the Point class header file

// Default constructor for the Point class
Point::Point()
{
    x = 0;  // Initialize x-coordinate to 0
    y = 0;  // Initialize y-coordinate to 0
}

// Parameterized constructor for the Point class
Point::Point(int x, int y)
{
    this->x = x;  // Initialize x-coordinate with the provided value
    this->y = y;  // Initialize y-coordinate with the provided value
}

// Destructor for the Point class
Point::~Point()
{
    // No dynamic memory to clean up, so the destructor is empty
}

// Method to get the x-coordinate
int Point::get_X() const
{
    return x;  // Return the x-coordinate
}

// Method to get the y-coordinate
int Point::get_Y() const
{
    return y;  // Return the y-coordinate
}

// Method to set the x-coordinate
void Point::set_X(int X)
{
    x = X;  // Update the x-coordinate with the provided value
}

// Method to set the y-coordinate
void Point::set_Y(int Y)
{
    y = Y;  // Update the y-coordinate with the provided value
}

// Overloaded equality operator to compare two Point objects
bool Point::operator==(const Point& p)
{
    if (this->x == p.x && this->y == p.y)  // Check if both coordinates are equal
        return true;  // Return true if the points are equal

    return false;  // Return false if the points are not equal
}

// Overloaded output stream operator to print Point objects
ostream& operator<<(ostream& o, const Point& p)
{
    o << endl;  // Print a newline
    o << "X: " << p.get_X() << endl;  // Print the x-coordinate
    o << "Y: " << p.get_Y() << endl;  // Print the y-coordinate
    return o;  // Return the output stream
}
