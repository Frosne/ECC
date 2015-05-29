#ifndef PHOPOINT_H
#define PHOPOINT_H
#include <givaro/givinteger.h>
#include "point.h"

typedef Modular<Integer> Field;
class PhoPoint
{

public:
    PhoPoint();
    PhoPoint(Integer a, Integer b, Point p);
    Field::Element a;
    Field::Element b;
    Point p;

    static bool isEquals(PhoPoint p1, PhoPoint p2);
};

#endif // PHOPOINT_H
