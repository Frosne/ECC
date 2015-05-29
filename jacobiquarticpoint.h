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

public:
    Modular<Integer> PointField;
    Modular<Integer>:: Element x,y,z;
    Point p;
    JacobiQuarticPoint(Integer field);
    JacobiQuarticPoint(Integer field, Givaro::Integer x, Givaro::Integer y, Givaro::Integer z, Point p);
    JacobiQuarticPoint(Curve c, Integer field, Point p);

    Point ToPoint();
    static Point ToPoint(JacobiQuarticPoint p);
};

#endif // JACOBIQUARTICPOINT_H
