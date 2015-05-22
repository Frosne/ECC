#include "point.h"
#include <givaro/givinteger.h>
#include <givaro/extension.h>

Point::Point(Integer field,Givaro::Integer x, Givaro::Integer y)
{
    Field _temp(field);
    this->PointField = _temp;
    PointField.init(this->x1,x);
    PointField.init(this->y1,y);

}

Point::Point ()
{
    this->x = 0;
    this->y = 0;
}

Givaro::Integer Point::getX ()
{
    return this->x;
}

Givaro::Integer Point::getY()
{
    return this->y;
}

bool Point::isEquals(Point p1, Point p2)
{
    if (p1.x1 == p2.x1 && p1.y1 == p2.y1)
        return true;
    else return false;
}

