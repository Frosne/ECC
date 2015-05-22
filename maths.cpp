#include "maths.h"
#include <givaro/extension.h>
#include <givaro/givinteger.h>
#include <givaro/modular.h>

typedef Modular<Integer> Field;
typedef Poly1Dom< Field, Dense> Polys;


using namespace Givaro;
mathS::mathS()
{


}

Integer mathS::Abs(Integer a, Integer b)
{
    if (a>b)
        return a-b;
    else
        return b-a;
}

Integer mathS::Pow(Integer base, Integer pow)
{
    if (pow == Integer::zero)
        return Integer::one;
    Integer temp = base;
    for (int i = 1; i<pow; i++)
        temp*=temp;

}

Integer mathS::PollandRho(Integer number)
{
    int const length = 1000;
    Integer arr [length];
    arr[0]=1;
    for (int i = 0; i<length; i++)
    {
        arr[i]=mathS::ComputePolynomial(arr[i-1],number);
    }

    Integer GCD = -1;
    for (int i = 1; i<length; i++)
    {
        for (int j = Pow(2,i)+1; j<Pow(2,i+1)-1; j++)
        {

           GCD = CheckGCDPho(Abs(arr[i],arr[j]),number);
           if (GCD != Integer::mOne)
           {
               break;
           }

        }
    }

    return GCD;
}

Integer mathS::PollandRhoPrime(Integer _number)
{
    Integer number = _number;

    int const length = 32000;
    Integer arr [length];
    Integer flag=Integer::mOne;

    arr[0]=1;
    for (int i = 1; i<length; i++)
    {
       arr[i]=mathS::ComputePolynomial(arr[i-1],number);
       if (i%2 ==0)
       {
          flag= mathS::CheckGCDPho(number, Abs(arr[i/2],arr[i]));
       }
       if (flag!=Integer::mOne)
       {
           break;
       }

    }


}
//TODO: DELETE!
Integer mathS::ComputePolynomial(Integer Point, Integer mod)
{
    Modular<Integer> field (mod);
    Modular<Integer>::Element _temp, _temp1,_point;

    field.assign(_point,Point);
    field.init(_temp,32767);
    field.init(_temp1,0);
    field.mul(_temp1,Point,Point);
    field.mul(_temp1,_temp1,1024);
    field.add(_temp,_temp,_temp1);
    return _temp;
}

Integer mathS::CheckGCDPho(Integer a, Integer b)
{
    IntegerDom domain;
    IntegerDom::Element GG;
    domain.gcd(GG,a,b);
    std::cout<<"Result:"<<GG<<std::endl;

  if (GG==Integer::one)
  {
      return Integer::mOne;
  }
  return GG;
}
