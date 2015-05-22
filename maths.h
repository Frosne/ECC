#ifndef MATHS_H
#define MATHS_H

#include <givaro/extension.h>
#include <givaro/givinteger.h>
#include <givaro/modular.h>

using namespace Givaro;

class mathS
{
public:
    mathS();

    // void static PrintPoint(Point p1);
    Integer PollandRhoPrime(Integer number);
    Integer static ComputePolynomial(Integer Point, Integer mod);
    Integer static ComputePolynomial(Integer Point, Integer xs, Integer x);
    Integer static CheckGCDPho(Integer a, Integer b);
    Integer static Abs(Integer a, Integer b);
    Integer static Pow(Integer a, Integer b);
    Integer static PollandRho(Integer number);

};

#endif // MATHS_H
