#ifndef MATHS_H
#define MATHS_H

#include <givaro/extension.h>
#include <givaro/givinteger.h>
#include <givaro/modular.h>

#include "point.h"
#include "curve.h"
#include "phopoint.h"
#include "patternmaker.h"
#include <list>

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
    PhoPoint GenerateBasePoint(Point base, Point q, Curve c);
    PhoPoint GenerateNewPoint(int counter, int period, PhoPoint Y, Point p, Point q, Curve c);
    PhoPoint GenerateNewPoint(int counter, Point base, Point q, Curve c, PatternMaker pm);
    void GenerateArray(int elements, Point base, Point q, Curve c, PhoPoint array[]);
    void CompareArray(PhoPoint array[],int elements, PhoPoint a, PhoPoint b);
    void CalculateD(PhoPoint p, PhoPoint q, Integer field, Integer result);

    void ComputePrimeNumbers(Integer q,  std::list<Integer> lst, int size);
    Integer GenerateNextPrime(Integer q);
};

#endif // MATHS_H
