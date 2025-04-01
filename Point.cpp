#include "Point.h"
#include <stdio.h> 

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Point::~Point() {
    // None
}

int Point::get_X() const {
    return x;
}

int Point::get_Y() const {
    return y;
}

void Point::set_X(int x) {
    this->x = x;
}

void Point::set_Y(int y) {
    this->y = y;
}

bool Point::equals(const Point& p) const {
    return (this->x == p.x && this->y == p.y);
}

void Point::print() const {
    printf("X: %d\n", x);
    printf("Y: %d\n", y);
}