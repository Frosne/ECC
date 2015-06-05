#ifndef JACOBIQUARTICPOINT_H
#define JACOBIQUARTICPOINT_H
#include <givaro/givinteger.h>
#include <givaro/extension.h>
#include <givaro/modular.h>
#include "point.h"
#include "curve.h"

using namespace Givaro;
typedef Modular<Integer> Field;

class JacobiQuarticPoint
{
    //TO THINK

public:
    Modular<Integer> PointField;
    Modular<Integer>:: Element x,y,z;
    Point p;
    //Constructors
    JacobiQuarticPoint(Integer field);
    //Point with Jacobian coordinated and point on the curve
    JacobiQuarticPoint(Integer field, Givaro::Integer x, Givaro::Integer y, Givaro::Integer z, Point p);
    //constructor from the point
    JacobiQuarticPoint(Curve c, Integer field, Point p);

    Point ToPoint();
    static Point ToPoint(JacobiQuarticPoint p);
};

#endif // JACOBIQUARTICPOINT_H
