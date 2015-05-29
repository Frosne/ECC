#include "phopoint.h"
#include "givaro/givinteger.h"
#include <point.h>
#include <string>

PhoPoint::PhoPoint()
{

}

PhoPoint::PhoPoint(Givaro::Integer a1, Givaro::Integer b1, Point p)
{
    this->p = p;
    this->p.PointField.init(this->a,a1);
    this->p.PointField.init(this->b,b1);
}

bool PhoPoint::isEquals (PhoPoint p1, PhoPoint p2)
{
    //  if (p1.a == p2.a && p1.b==p2.b && Point::isEquals(p1.p,p2.p))
    if (Point::isEquals(p1.p,p2.p))
        return true;
    else
        return false;
}


