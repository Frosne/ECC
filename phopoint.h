#ifndef PHOPOINT_H
#define PHOPOINT_H
#include <givaro/givinteger.h>
#include "point.h"

class PhoPoint
{
public:
    PhoPoint();
    PhoPoint(Integer a, Integer b, Point p);
    Givaro::Integer a;
    Givaro::Integer b;
    Point p;
};

#endif // PHOPOINT_H
