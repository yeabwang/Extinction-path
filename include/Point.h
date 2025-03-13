#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point();
    Point(int x, int y);
    int get_X() const;
    int get_Y() const;
    void set_X(int x);
    void set_Y(int y);
    virtual ~Point();

    bool equals(const Point& p) const;
    void print() const;

protected:
    int x;
    int y;
};

#endif // POINT_H