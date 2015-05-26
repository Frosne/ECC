#include "phopoint.h"
#include "givaro/givinteger.h"
#include <point.h>
#include <string>

PhoPoint::PhoPoint()
{

}

PhoPoint::PhoPoint(Givaro::Integer a1, Givaro::Integer b1, Point p)
{
    this->a = a1;
    this->b = b1;
    this->p = p;
}


