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
#include <vector>

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




    mathS math;
       std::vector<Integer> v;
        v = math.ComputePrimeNumbers(Integer(100));

        Curve c(17,0,0,0,2,2);
     // int res =  math.ComputeT(Integer(17),c);

        mathS::SchoffsAlgorithm(Integer(17),c);
      // std::cout<< mathS::ComputeQModL(Integer(2321442142206),Integer(5))<<std::endl;
       //mathS::ComputeNotQ();*/

}


