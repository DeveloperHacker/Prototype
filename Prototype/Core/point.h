#ifndef POINT_H
#define POINT_H

#include <QtCore>

class Point
{
public:
    Point() = default;
    Point(int x, int y) : x(x), y(y) {}
    ~Point() = default;

    int x;
    int y;
    bool operator ==(Point temp) const;
    bool operator !=(Point temp) const;
};


#endif // POINT_H
