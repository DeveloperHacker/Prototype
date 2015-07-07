#ifndef POINT_H
#define POINT_H

#include <QtCore>

class Point
{
public:
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    ~Point() = default;

    int x;
    int y;
    const Point &operator =(Point temp);
    bool operator ==(Point temp) const;
    bool operator !=(Point temp) const;
};


#endif // POINT_H
