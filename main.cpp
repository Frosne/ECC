#include <iostream>
#include <givaro/givinteger.h>
#include <givaro/extension.h>
#include <givaro/modular.h>
#include <math.h>
#include <curve.h>
#include <printer.h>
#include <searchoutput.h>
#include "maths.h"

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


     /*Field Z101( 101, 1 );
     Polys DP101( Z101, Indeter("Y"));

     Polys::Element P, Q,R;

     Field::Element temp;
     Z101.init(temp,4);

     DP101.assign(P,temp);
     DP101.write(std::cout<<"P:",P)<<std::endl;


     DP101.init(Q,Degree(1),33UL);
     DP101.write(std::cout<<"Q:",Q)<<std::endl;

     DP101.addin(P,Q);
     DP101.write(std::cout<<"P:",P)<<std::endl;

     DP101.init(Q,Degree(2),100003UL);
    // DP101.write(std::cout<<"Q:",Q)<<std::endl;

     DP101.addin(P,Q);
     DP101.write(std::cout<<"P:",P)<<std::endl;

     //_____________________________________________________

     DP101.mul(R,P,Q);
     // multiplication

     DP101.gcd(R,P,Q); //gcd of 2 polynoms

     Degree dP;
     DP101.degree(dP,P);

     std::cout<<"Q:"<<dP<<std::endl;

     // get Degree of polynoms

     //_____________________________________________________
     Givaro::Integer a("767676");
     std::cout<<"A: "<<a<<std::endl;
*/

  Curve curve (127,0,0,0,2,2);
  printer::PrintCurve(curve);

  Point p(127,5,1);
  Point temp =p;

/*
    for (int i = 0; i<60; i++)
    {
        std::cout<<i<<std::endl;
        printer::PrintPoint(curve.ComputeMultiplicationByMSB(p,i));

    }

    std::cout<<std::endl;
    std::cout<<std::endl;
    Integer d = 48;
    Point pCorrect = curve.ComputeMultiplicationByMSB(p,d);
    printer::PrintPoint(pCorrect);

    d = ChangeD(d,2);
    std::cout<<"D: "<<d<<std::endl;
    Point pUncorrect = curve.ComputeMultiplicationByMSB(p,d);
    printer::PrintPoint(pUncorrect);

   SearchOutput out = curve.SearchPoint(pCorrect,pUncorrect,p);
   std::cout<<"Result: "<<out.position<<std::endl;
*/
/*  Integer d = 48;
 curve.RebuildD(6,p,d);*/

 /* temp = p;
  for (int i = 1; i<127; i++){
      std::cout<<i;
      printer::PrintPoint(curve.ComputeMultiplicationByMSB(p,i));
      temp = curve.PointAddiction(temp,p);
      printer::PrintPoint(temp);
  }

  NewLine();
  NewLine();

  Integer d = 126;
  Point real = curve.ComputeMultiplicationByMSB(p,d);
  printer::PrintPoint(real);

  //+
  Integer result = curve.DLPNaive(real,p,101);
    std::cout<<result<<std::endl;

    */

  //mathS::PollandRhoPrime(2);

  Integer test = 96511250482432409;
 std::cout<<mathS::PollandRho(test)<<std::endl;

return 0;
}


