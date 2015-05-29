#include <iostream>
#include <givaro/givinteger.h>
#include <givaro/extension.h>
#include <givaro/modular.h>
#include <math.h>
#include <curve.h>
#include <printer.h>
#include <searchoutput.h>
#include "maths.h"
#include "patternmaker.h"
#include <list>

using namespace Givaro;

//typedef GFqDom<int> Field;
typedef Modular<Integer> Field;

void NewLine()
{
    std::cout<<std::endl;
}

/*bool getBitd(Integer x, int pos)
{

   bool temp =  ( ((x) & ( Integer::one << (pos) )) !=0 );
   return temp;
}

Integer powInteger(Integer a, Integer power)
{

    Integer _temp  = Integer::one;
    for (int i = 0; i<power; i++)
        _temp = a * _temp;
    return _temp;
}

Integer ChangeD(Integer d, Integer random)
{
    Integer newd = d;
    Integer two = 2;
    Integer i = random;
    two = powInteger(two,i);

    if (getBitd(d,i)==0)
    {
         newd = d + two;
    }
    else
    {
         newd = d - two;
    }

    return newd;
}
*/

int main(int argc, char * * argv) {

   Curve c ;
   Curve c1{100};
   Curve c2{100,2,2};
   Curve c3{100,1,2,3,4,5};

   printer::PrintCurve(c);
   printer::PrintCurve(c1);
   printer::PrintCurve(c2);
   printer::PrintCurve(c3);
return 0;
}


