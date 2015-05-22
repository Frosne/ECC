#include <iostream>
#include <givaro/givinteger.h>
#include <givaro/extension.h>
#include <givaro/modular.h>
#include "searchoutput.h"
#ifndef CURVE_H
#define CURVE_H


#include <point.h>

using namespace Givaro;
typedef Modular<Integer> Field;


class Curve
{

public:
          Field CurveField;
         // Polys CurvePoly;

          Field::Element a1,a2,a3,a4,a6;


        //main part of the curve
        int characteristic;
        int order;
        Integer diskriminant;

        //additional information
        Field::Element d2, d4, d6, d8;

        //1,0..0
         Curve();
         Curve(Integer field, Integer a1, Integer a2, Integer a3, Integer a4, Integer a6);


         bool IsPointOnCurve(Point p);
         bool IsCurvesEqual(Curve c1);
         void ComputeParameters();
         int ComputeOrder();
         void ComputeHassInterval();
         Point PointAddiction(Point p1, Point p2);
         Point ComputeMultiplicationByMSB(Point p, Integer d);

         SearchOutput SearchPoint(Point real, Point changed, Point base);
         Integer RebuildD(int keyLength, Point base, Integer d);

         Integer DLPNaive(Point real, Point Base, Integer order);


};
#endif // CURVE_H

