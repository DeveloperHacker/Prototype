#include "Core/point.h"

const Point& Point::operator =(Point temp)
{
    this->x = temp.x;
    this->y = temp.y;

    return *this;
}

bool Point::operator ==(Point temp) const
{
    if ( (temp.x == x) && (temp.y == y) ) return true;
    else return false;
}

bool Point::operator !=(Point temp) const
{
    if (temp == *this) return false;
    else return true;
}
