#include "maths.h"
#include <givaro/extension.h>
#include <givaro/givinteger.h>
#include <givaro/modular.h>

#include "printer.h"
#include "phopoint.h"

#include <list>

typedef Modular<Integer> Field;
typedef Poly1Dom< Field, Dense> Polys;

static int timer = 0;
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
        temp*=base;
    return temp;
}

Integer mathS::PollandRho(Integer number)
{
    int const length = 32000;
    Integer arr [length];
    arr[0]=1;
    for (int i = 1; i<4; i++)
    {
        arr[i]=mathS::ComputePolynomial(arr[i-1],number);
    }




    Integer GCD = -1;
    for (Integer i = 1; i<length; i++)
    {

        for (Integer j = Pow(2,i); j<Pow(2,i+1); j++)
        {
            GCD = CheckGCDPho(Abs(arr[i],arr[j]),number);

           if (GCD != Integer::mOne)
           {
              std::cout<<arr[i]<< "    " << arr[j]<<std::endl;
              return GCD;
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
    if (a==Integer::zero)
        return Integer::mOne;
    IntegerDom domain;
    IntegerDom::Element GG;
    domain.gcd(GG,a,b);

  if (GG==Integer::one)
  {
      return Integer::mOne;
  }
  return GG;
}

PhoPoint mathS::GenerateBasePoint(Point base, Point q, Curve c)
{
    Integer a0 = Integer::random_between(1,10)%10;
    std::cout<<"a0:"<<a0<<std::endl;
    Integer b0 = Integer::random_between(1,10)%10;


    Point a =  c.ComputeMultiplicationByMSB(base,a0);
    Point b =  c.ComputeMultiplicationByMSB(q,b0);

    Point _q = c.PointAddiction(a,b);

    PhoPoint point;
    point.a = base.PointField.init(point.a,a0);
    point.b = base.PointField.init(point.b,b0);
    point.p = _q;

    printer::Print(1,"BasePoint:");
    printer::PrintRhoPoint(point);
    return point;

}

PhoPoint mathS::GenerateNewPoint(int counter,int period,PhoPoint Y, Point p, Point q, Curve c)
{
    PhoPoint result;
    if (counter%period==0)
    {
        result.p = c.PointAddiction(Y.p,p);

        Y.p.PointField.assign(result.b,Integer::zero);
        Y.p.PointField.assign(result.a,Integer::zero);

        Y.p.PointField.add(result.a,Y.a,1);
        Y.p.PointField.assign(result.b,Y.b);
       // result.a = Y.a + 1;
        //result.b = Y.b;
    }
    else if (counter%period ==1)
    {
        result.p = c.PointAddiction(Y.p,q);
        Y.p.PointField.assign(result.b,Integer::zero);
        Y.p.PointField.assign(result.a,Integer::zero);
        Y.p.PointField.add(result.b,Y.b,1);
        Y.p.PointField.assign(result.a,Y.a);
    }
    else if (counter%period==2)
    {
        Integer two (2);
        result.p = c.PointAddiction(Y.p,Y.p);

        Y.p.PointField.assign(result.b,Integer::zero);
        Y.p.PointField.assign(result.a,Integer::zero);

        Y.p.PointField.mul(result.a,Y.a,two);
        Y.p.PointField.mul(result.b,Y.b,2);

       /* result.a = Y.a *2;
        result.b = Y.b *2;*/
    }
    return result;

}

//PhoPoint mathS::GenerateNewPoint(int counter, Point base, Point q, Curve c, PatternMaker pm);

void mathS::GenerateArray(int elements, Point base, Point q, Curve c, PhoPoint array[])
{

   PhoPoint y0= this->GenerateBasePoint(base,q,c);
   array[0] = y0;

   for (int i = 1; i<elements; i++)
   {
       array[i]=this->GenerateNewPoint(i,3,array[i-1],base,q,c);
   }

   return;
}

void mathS::CompareArray(PhoPoint array[],int elements, PhoPoint a, PhoPoint b)
{
    for (int i = 0; i<elements-1; i++)
    {
        for (int j = i; j<elements-1; j++)
        {
            if (PhoPoint::isEquals(array[i],array[j]) && (i!=j))
            {
                a = array[i];
                b = array[j];
                printer::Print("Point detected");
                printer::PrintRhoPoint(a);
                printer::PrintRhoPoint(b);
                printer::Print("Point detected");
                return;
            }
        }
    }

     printer::Print("Point detected");
     return;
}

void mathS::CalculateD(PhoPoint a, PhoPoint b, Integer field, Integer result)
{
    IntegerDom dom;
    Integer _gcd;
    dom.gcd(_gcd,mathS::Abs(b.b,a.a),field);
    if (_gcd==1)
    {
        Field::Element _temp,_temp2;
        a.p.PointField.assign(_temp,Integer::zero);
        a.p.PointField.assign(_temp2,Integer::zero);

        a.p.PointField.sub(_temp,b.b,a.b);
        a.p.PointField.inv(_temp,_temp);

        a.p.PointField.sub(_temp2,b.a,b.b);
        a.p.PointField.mul(_temp,_temp,_temp2);

        result = _temp;
    }
}

Integer mathS::GenerateNextPrime(Integer last)
{
    IntPrimeDom IP;
    IntPrimeDom::Element m;
    IP.nextprime(m,last);
    return m;
}

void mathS::ComputePrimeNumbers(Integer q, std::list<Integer> res, int size)
{
    size+=1;
    return;


}
