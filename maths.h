#ifndef MATHS_H
#define MATHS_H

#include <givaro/extension.h>
#include <givaro/givinteger.h>
#include <givaro/modular.h>

#include "point.h"
#include "curve.h"

using namespace Givaro;

class mathS
{
public:
    mathS();

    // void static PrintPoint(Point p1);
    Integer static PollandRhoPrime(Integer number);
    Integer static ComputePolynomial(Integer Point, Integer mod);
    Integer static ComputePolynomial(Integer Point, Integer xs, Integer x);
    Integer static CheckGCDPho(Integer a, Integer b);
    Integer static Abs(Integer a, Integer b);
    Integer static Pow(Integer a, Integer b);
    Integer static PollandRho(Integer number);
    struct PhoPoint GenerateBasePoint(Point base, Point q, Curve c);

};

#endif // MATHS_H
