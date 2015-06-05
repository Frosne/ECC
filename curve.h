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
        Field::Element a1,a2,a3,a4,a6;

        Integer order;
        Integer diskriminant;
        Field::Element d2, d4, d6, d8;

        //constructors
        Curve();
        Curve(Integer field);
        Curve(Integer field, Integer a, Integer b);
        Curve(Integer field, Integer a1, Integer a2, Integer a3, Integer a4, Integer a6);

        //compute additional information
        void ComputeParameters();
        //todo
        void ComputeOrder();
        void ComputeHassInterval();

        //Compare
        bool IsPointOnCurve(Point p);
        bool IsCurvesEqual(Curve c1);

        //Point operation on curve
        Point PointAddition(Point p1, Point p2);
        Point ComputeMultiplicationByMSB(Point p, Integer d);
        //todo
        Point ComputeMultiplicationByLSB(Point p, Integer d);
        //todo
        Integer ComputePointOrder(Point p);

        //Derivided
        SearchOutput SearchPoint(Point real, Point changed, Point base);
        Integer RebuildD(int keyLength, Point base, Integer d);

        //Algorithms
        Integer DLPNaive(Point real, Point Base, Integer order);


         private:
         void Initialization(Integer field, Integer a1, Integer a2, Integer a3, Integer a4, Integer a6);
};
#endif // CURVE_H

