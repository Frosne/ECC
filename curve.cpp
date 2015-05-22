

#include <iostream>
#include <givaro/givinteger.h>
#include <givaro/extension.h>

#include "curve.h"
#include "printer.h"
#include "searchoutput.h"

#include <random>
#include <string.h>

using namespace Givaro;

//Default constructor
Curve::Curve()
{
    //this->Curve(1,0,0,0,0,0);
}

Curve::Curve(Integer field, Integer a1, Integer a2, Integer a3, Integer a4, Integer a6)
{

    Field _temp (field);

    this->CurveField = _temp;

    Field::Element elem;
    CurveField.init(elem,2);

    this->CurveField.init(this->a1,a1);
    this->CurveField.init(this->a2,a2);
    this->CurveField.init(this->a3,a3);
    this->CurveField.init(this->a4,a4);
    this->CurveField.init(this->a6,a6);

}

void Curve::ComputeParameters()
{/*
    Field::Element temp1, temp2, temp3, temp4, temp5;
    CurveField.assign(temp1,0);
    CurveField.assign(temp2,0);
    CurveField.assign(temp3,0);
    CurveField.assign(temp4,0);
    CurveField.assign(temp5,0);

    CurveField.mul(temp1, this->a1,this->a1);
    CurveField.mul(temp2,4,this->a2);
    CurveField.add(this->d2,temp1,temp2);

    CurveField.mul(temp1,4,this->a4);
    CurveField.mul(temp2,this->a1, this->a3);
    CurveField.add(this->d4,temp1,temp2);

    CurveField.mul(temp1,this->a3,this->a3);
    CurveField.mul(temp2,4, this->a6);
    CurveField.add(this->d6,temp1,temp2);

    CurveField.mul(temp1, this->a1, this->a1);
    CurveField.mul(temp1,temp1, this->a6);
    CurveField.mul(temp2,4, this->a2);
    CurveField.mul(temp2,temp2, this->a6);
    CurveField.mul(temp3,-1, this->a1);
    CurveField.mul(temp3, temp3,this->a3);
    CurveField.mul(temp3,temp3, this->a4);
    CurveField.mul(temp4,this->a2, this->a3);
    CurveField.mul(temp4,temp4,this->a3);
    CurveField.mul(temp5,-1,this->a4);
    CurveField.mul(temp5,temp5, this->a4);
    CurveField.add(this->d8,temp1,temp2);
    CurveField.add(this->d8,this->d8,temp3);
    CurveField.add(this->d8,this->d8,temp4);
    CurveField.add(this->d8,this->d8,temp5);

    CurveField.mul(temp1,this->a1, this->a1, this->a6);
    CurveField.mul(temp2,4, this->a2, this->a6);
    CurveField.mul(temp3,-1, this->a1, this->a3, this->a4);
    CurveField.mul(temp4,this->a2, this->a3, this->a3);
    CurveField.mul(temp5,-1,this->a4,this->a4);
    CurveField.add(this->d8,temp1,temp2,temp3,temp4,temp5);


*/
}

bool getBit(Integer x, int pos)
{

   bool temp =  ( ((x) & ( Integer::one << (pos) )) !=0 );
   return temp;
}

bool getBitd(Integer x, int pos)
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

bool Curve::IsPointOnCurve(Point p)
{
    Field::Element temp, temp1, temp2;
    CurveField.init(temp,0);
    CurveField.init(temp1,0);
    CurveField.init(temp2,0);

    CurveField.mul(temp1,p.y1,p.y1);
    CurveField.mul(temp2,p.x1,p.y1);
    CurveField.mul(temp2,temp2,this->a1);
    //first 2
    CurveField.add(temp,temp1,temp2);

    CurveField.mul(temp1,this->a3,p.y1);
    CurveField.add(temp,temp,temp1);

    CurveField.mul(temp1,p.x1,p.x1);
    CurveField.mul(temp2,p.x1,-1);
    CurveField.mul(temp1,temp1,temp2);
    CurveField.add(temp,temp,temp1);

    CurveField.mul(temp1,p.x1,p.x1);
    CurveField.mul(temp2,p.x1,this->a2);
    CurveField.mul(temp1,temp1,temp2);
    CurveField.add(temp,temp,temp1);

    CurveField.mul(temp1,p.x,1);
    CurveField.mul(temp2,-1,this->a4);
    CurveField.mul(temp1,temp1,temp2);
    CurveField.add(temp,temp,temp1);

    CurveField.mul(temp1,p.x1,p.x1);
    CurveField.mul(temp2,p.x1,-1);
    CurveField.mul(temp1,temp1,temp2);
    CurveField.add(temp,temp,temp1);

    CurveField.mul(temp1,-1,this->a6);
    CurveField.add(temp,temp,temp1);

    CurveField.init(temp2,0);
   // if (temp==0)??
    // if (temp==temp2)

    if (temp==temp2)
   // if (CurveField.operator ==(temp,temp2))
        return true;
    else
        return false;
}

Point Curve::PointAddiction(Point p1, Point p2)
{
    Field::Element lambda, temp, temp1, temp2, x, y;
    CurveField.init(lambda,0);
    CurveField.init(temp,0);
    CurveField.init(temp1,0);
    CurveField.init(temp2,0);
    CurveField.init(x,0);
    CurveField.init(y,0);

    bool compare = Point::isEquals(p1,p2);

    if (compare)
    {
        CurveField.mul(temp1,p1.x1,p1.x1);
        CurveField.mul(temp1,temp1,3);


        CurveField.mul(temp2,this->a2,p1.x1);
        CurveField.mul(temp2,temp2,2);

        CurveField.add(temp,temp1, temp2);
        CurveField.add(temp,temp,this->a4);

        CurveField.mul(temp1,this->a1,p1.y1);
        CurveField.mul(temp1,temp1,-1);
        CurveField.add(temp,temp,temp1);

        CurveField.mul(temp1,2,p1.y1);
        CurveField.mul(temp2,this->a1, p1.x1);
        CurveField.add(temp1,temp1,temp2);
        CurveField.add(temp1,temp1,this->a3);

        CurveField.inv(temp1,temp1);
        CurveField.mul(lambda,temp,temp1);

    }
    else
    {
        CurveField.sub(temp,p2.y1,p1.y1);
        CurveField.sub(temp1,p2.x1,p1.x1);
        CurveField.inv(temp1,temp1);
        if (CurveField.isZero(temp1)==1)
        {
            printer::Print(1, "next point will be out of curve");
        }
        CurveField.mul(lambda,temp,temp1);
    }

    CurveField.mul(temp,lambda,lambda);
    CurveField.mul(temp1,this->a1, lambda);
    CurveField.add(x,temp,temp1);
    CurveField.sub(x,x,this->a2);
    CurveField.sub(x,x,p1.x1);
    CurveField.sub(x,x,p2.x1);

    CurveField.sub(temp,x,p1.x1);
    CurveField.mul(temp,temp,lambda);
    CurveField.mul(temp1,this->a1,x);
    CurveField.sub(y,y,p1.y1);
    CurveField.sub(y,y,temp);
    CurveField.sub(y,y,temp1);
    CurveField.sub(y,y,this->a2);


    Point pt;
    pt.x1 = x;
    pt.y1 = y;

    return pt;


}

Point Curve::ComputeMultiplicationByMSB(Point p, Integer d)
{

    Point H = p;

    for (int i = d.bitsize()-2; i>=0; i--)
    {
          H= this->PointAddiction(H,H);
          if (getBit(d,i))
            H = this->PointAddiction(H,p);
    }
    return H;
}

SearchOutput Curve::SearchPoint(Point real, Point changed, Point base)
{

    SearchOutput out;

    Integer lengthD = 20;
    Point _base = base;
    Point _temp = real, __temp = changed;
    for (int i = 1; i<lengthD; i++)
    {
        if (i > 1)
        {
            _base = this->PointAddiction(_base,_base);
        }



        _temp = this->PointAddiction(real,_base);

        __temp = this->PointAddiction(changed,_base);


        if (Point::isEquals(changed,_temp))
        {
            SearchOutput out;
            out.direction = 1;
            out.position = i-1;
            return out;
        }

        if (Point::isEquals(real,__temp))
        {
            SearchOutput out;
            out.direction = 0;
            out.position = i-1;
            return out;
        }
    }

    out.direction = 0;
    out.position = -1;

    return out;
}

Integer Curve::RebuildD(int keyLength,Point base, Integer d)
{
    Integer _tempd;
    Integer result = 0;
    Point real = this->ComputeMultiplicationByMSB(base,d);

     for (int i = 0; i<=keyLength; i++)
    {
       int random = std::rand()%keyLength;
        _tempd = ChangeD(d,i);

        Point _temppoint=  this->ComputeMultiplicationByMSB(base,_tempd);

        SearchOutput _tempoutput = this->SearchPoint(real,_temppoint,base);


        std::cout<<_tempoutput.direction<<"___"<<_tempoutput.position<<std::endl;

        /*Integer two (2);
        Integer _sh = powInteger(two,keyLength)-1;


        if (_tempoutput.direction)
            _sh = _sh - powInteger(two, _tempoutput.position);
        else
            _sh = _sh + powInteger(two, _tempoutput.position);
        */

         std::cout<<result<<std::endl;

         Integer one = 1;
        if (_tempoutput.direction)
            result |= (((Integer)one)<<((unsigned long)_tempoutput.position));
        else
            result &=~(Integer::one<<((unsigned long)_tempoutput.position));

        std::cout<<result<<std::endl;
      //  std::cout<<result<<std::endl;


    }

     return result;
}

Integer Curve::DLPNaive(Point real, Point Base, Integer order)
{
    Integer two = 2;
    if (order > powInteger(2,30))
    {
        printer::Print(1,"may take too much time");
    }
    //Integer d;
    if (Point::isEquals(real,Base))
        return 1;
    Point temp = Base;
    for (Integer i = 2; i<order; i++)
    {
       printer::PrintPoint(temp);
       temp =  this->PointAddiction(temp,Base);

       if (Point::isEquals(temp,real))
           return i;
       if (i %1000==0)
       {
           std::cout<<i<<std::endl;
       }
    }

    return -1;
}
