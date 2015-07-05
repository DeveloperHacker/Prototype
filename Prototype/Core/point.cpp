#include "Core/point.h"

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
