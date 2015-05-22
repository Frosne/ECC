#ifndef POINT_H
#define POINT_H
#include <givaro/givinteger.h>
#include <givaro/extension.h>
#include <givaro/modular.h>




using namespace Givaro;
typedef Modular<Integer> Field;

class Point
{

public://INteger
    Modular<Integer> PointField;
    Modular<Integer>:: Element x1,y1;


    Point(Integer field, Givaro::Integer x, Givaro::Integer y);
    Givaro::Integer getX();
    Givaro::Integer getY();
    Point();
    Givaro::Integer x;
    Givaro::Integer y;
    static bool isEquals(Point p1, Point p2);

};

#endif // POINT_H


