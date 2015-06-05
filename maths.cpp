#include "maths.h"
#include <givaro/extension.h>
#include <givaro/givinteger.h>
#include <givaro/modular.h>

#include <givaro/givpower.h>
#include <givaro/givquotientdomain.h>

#include "printer.h"
#include "phopoint.h"

#include <list>
#include <vector>



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

    Point _q = c.PointAddition(a,b);

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
        result.p = c.PointAddition(Y.p,p);

        Y.p.PointField.assign(result.b,Integer::zero);
        Y.p.PointField.assign(result.a,Integer::zero);

        Y.p.PointField.add(result.a,Y.a,1);
        Y.p.PointField.assign(result.b,Y.b);
       // result.a = Y.a + 1;
        //result.b = Y.b;
    }
    else if (counter%period ==1)
    {
        result.p = c.PointAddition(Y.p,q);
        Y.p.PointField.assign(result.b,Integer::zero);
        Y.p.PointField.assign(result.a,Integer::zero);
        Y.p.PointField.add(result.b,Y.b,1);
        Y.p.PointField.assign(result.a,Y.a);
    }
    else if (counter%period==2)
    {
        Integer two (2);
        result.p = c.PointAddition(Y.p,Y.p);

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

std::vector<Integer> mathS::ComputePrimeNumbers(Integer q)
{
    std::vector<Integer> res;
    res.push_back(Integer(1));
    Integer mult(1),last(1);
    while(mult<=4*q)
    {
      last = mathS::GenerateNextPrime(last);
      mult*=last;
      res.push_back(last);
    }
    return res;

}

//fp
int mathS::ComputeT(Integer q, Curve c)
{
    Field _temp=c.CurveField;
    Polys dom (_temp,Indeter("Y"));
    Polys::Element p,p1,_tempP,one;
    Field::Element FEtemp;

    c.CurveField.init(FEtemp, Integer(1));
    dom.init(p,Degree(3),FEtemp);
    dom.init(p1,Degree(q),FEtemp);
    dom.init(one,Degree(0),FEtemp);

    c.CurveField.init(FEtemp,Integer(-1));
    dom.init(_tempP,Degree(1),FEtemp);
    dom.add(p1,p1,_tempP);

    c.CurveField.init(FEtemp,c.a4);
    dom.init(_tempP,Degree(1),FEtemp);
    dom.add(p,p,_tempP);
    c.CurveField.init(FEtemp,c.a6);
    dom.init(_tempP,FEtemp);
    dom.add(p,p,_tempP);

    dom.gcd(_tempP,p1,p);


     dom.write(std::cout << "p1 ", p1) << std::endl;
    return _tempP.areEqual(one);

}

Bivariates::Element mathS::CreatePolynomial(Integer power,Curve c)
{
    std::cout<<"Computing Polynom power "<<power<<std::endl;

    Field Zp = c.CurveField;
    Polys PZp(Zp,Indeter("X"));
    Bivariates PPZp(PZp,Indeter("Y"));
    Field::Element tmp,tmp2;
    Polys::Element P,R;
    Bivariates::Element Q;

    if (power == Integer::zero || power==Integer::one)
    {
        PZp.init(P,power);
        PPZp.init(Q,Degree(0));
        PZp.assign(Q[0],P);
        PPZp.write(std::cout << "Q_:   ", Q) <<"  power:  "<<power << std::endl;
        return Q;
    }

    else if (power>Integer(1) && power<=Integer(4))
    {
        if (power%2 ==0)
            PPZp.init(Q,Degree(1));
        else
            PPZp.init(Q,Degree(0));

        if (power==Integer(2))
        {
            PZp.init(P,Integer(2));
            PZp.assign(Q[1],P);
        }
        if (power==Integer(4))
        {

            PZp.init(P,Integer(4));
            PZp.assign(Q[1],P);
            PZp.init(R,Degree(6));
            Zp.mul(tmp,Integer(5),c.a4);
            Zp.assign(R[4],tmp);
            Zp.mul(tmp,Integer(20),c.a6);
            Zp.assign(R[3],tmp);
            Zp.mul(tmp,Integer(-5),c.a4);
            Zp.mul(tmp,tmp,c.a4);
            Zp.assign(R[2],tmp);
            Zp.mul(tmp,Integer(-4),c.a4);
            Zp.mul(tmp,tmp,c.a6);
            Zp.mul(tmp,Integer(-4),c.a4);
            Zp.mulin(tmp,c.a6);
            Zp.assign(R[1],tmp);
            Zp.mul(tmp,Integer(-8),c.a6);
            Zp.mul(tmp,tmp,c.a6);
            Zp.init(tmp2,Integer(-1));
            Zp.mul(tmp2,tmp2,c.a4);
            Zp.mul(tmp2,tmp2,c.a4);
            Zp.mul(tmp2,tmp2,c.a4);
            Zp.add(tmp,tmp,tmp2);
            Zp.assign(R[0],tmp);
            PZp.assign(Q[0],R);
        }
        else if(power==Integer(3))
        {
            PZp.init(R,Degree(4));
            Zp.assign(R[4],Integer(3));

            Zp.mul(tmp,Integer(6),c.a4);
            Zp.assign(R[3],tmp);
            Zp.mul(tmp,Integer(12),c.a6);
            Zp.assign(R[2],tmp);

            Zp.mul(tmp,Integer(-1),c.a4);
            Zp.mul(tmp,tmp,c.a4);
            Zp.assign(R[0],tmp);
            PZp.assign(Q[0],R);
        }
        PPZp.write(std::cout << "Q_: ", Q) <<"power:"<<power << std::endl;
        return Q;
    }
    else if (power > Integer(4)&&power%2 ==1)
    {
        Integer m = power/2;
        Bivariates::Element mm1,m_,mp1,mp2,_temp,_temp2,el;

        mm1 = CreatePolynomial(m-1,c);
        /*PPZp.write(std::cout<<"-->"<<mm1<<std::endl);
        PPZp.assign(mm1,CreatePolynomial(m-1,c));
        PPZp.write(std::cout<<"-->"<<mm1<<std::endl);
        */
        m_ = CreatePolynomial(m,c);
        PPZp.write(std::cout<<"->"<<m_<<std::endl);
        mp1 = CreatePolynomial(m+1,c);
        mp2 = CreatePolynomial(m+2,c);

       PPZp.mul(_temp,m_,m_);

       PPZp.mulin(_temp,m_);
       PPZp.write(std::cout<<"-->"<<_temp<<std::endl);
       /*PPZp.mul(_temp,_temp,m_);
       PPZp.write(std::cout<<"-->"<<_temp<<std::endl);*/

       PPZp.mulin(_temp,mp2);

       _temp2 = mp1;
       PPZp.write(std::cout<<"-->Temp2"<<_temp2<<std::endl);
       PPZp.mulin(_temp2,mp1);
       PPZp.write(std::cout<<"-->Temp2"<<_temp2<<std::endl);
       PPZp.mulin(_temp2,mp1);
       PPZp.write(std::cout<<"-->Temp2"<<_temp2<<std::endl);
       PPZp.mulin(_temp2,mm1);

       PPZp.subin(_temp,_temp2);
       PPZp.write(std::cout<<"Division Polynom"<<_temp<<"power:"<<power <<std::endl);
       return _temp;
    }

    else
    {
        Integer m = power/2;
        Bivariates::Element mm1,mm2,m_,mp1,mp2,_two,_temp,_temp2;
        mm1 = CreatePolynomial(m-1,c);
        mm2 = CreatePolynomial(m-2,c);
        m_ = CreatePolynomial(m,c);
        mp1 = CreatePolynomial(m+1,c);
        mp2 = CreatePolynomial(m+2,c);
        _two = CreatePolynomial(2,c);

        PPZp.mul(_temp,mm1,mm1);
        PPZp.mul(_temp,_temp,mp2);

        PPZp.mul(_temp2,mp1,mp1);
        PPZp.mul(_temp2,_temp2,mm2);

        PPZp.sub(_temp,_temp,_temp2);
        PPZp.mul(_temp,_temp,m_);
        PPZp.div(_temp,_temp,_two);

        PPZp.write(std::cout<<"Division Polynom"<<_temp<<"power:"<<power <<std::endl);
        return _temp;

    }
   /* Modular<Integer> Zp( "1234567891234567919" );  // integers modulo 1234567891234567919
       typedef Modular<Integer> Field;
       typedef Poly1Dom< Field, Dense> Polynomials;
       typedef Poly1Dom< Polynomials, Dense> Bivariates;
    // Polynomials over Z13, with X as indeterminate
    Polynomials PZp( Zp, Indeter("X") );
    Bivariates  PPZp( PZp, Indeter("Y") );

    Field::Element tmp;
    Polynomials::Element P, R;
    PZp.init(P, Degree(1), Zp.init(tmp,5) ); // 5X
    PZp.addin(P, Zp.init(tmp,7) ); // 5X+7

    PZp.init(R, Degree(3), Zp.init(tmp,11) ); // 11X^3
    PZp.addin(R, Zp.init(tmp,13) ); // 11X^3+13

    Bivariates::Element Q;
    PPZp.init(Q, Degree(2));
    PZp.assign(Q[0], R);
    PZp.assign(Q[2], P);// (5X+7)Y^2 + 11X^3+13


    PPZp.write(std::cout << "Q: ", Q) << std::endl;
*/

}


std::list<Bivariates::Element> mathS::RingTest(Curve c, Bivariates::Element el, int power)
{


    std::cout<<"Test"<<std::endl;
    Modular<Integer> Zp = c.CurveField;
    Polys PZp( Zp, Indeter("X") );
    Bivariates  PPZp( PZp, Indeter("Y") );
    Bivariates::Element temp;
    std::cout<<"_________________________________"<< std::endl;
    PPZp.write(std::cout<<temp<<std::endl);
    temp = el;
    std::cout<<"_________________________________"<< std::endl;
    PPZp.write(std::cout<<temp<<std::endl);
    std::cout<<"_________________________________"<< std::endl;

       typedef QuotientDom<Bivariates> BivMods;

       BivMods QD(PPZp,el);
       BivMods::Element Res, G,Gy;
       QD.init(Res); QD.init(G);

       Polys::Element P, R, S;
       PZp.assign(P, Degree(1), 1 ); 	// X
       PPZp.init(G, Degree(0), 1); 	// 1
       PPZp.init(Gy,Degree(1),1); // Y
       PZp.assign(G[0],P);
         PPZp.write(std::cout,G);

       std::list<Bivariates::Element> lst;


       long l = power;
       dom_power(Res, G, l, QD); 		// G^l mod Q

       QD.write(std::cout << "(X)^" << l << ": ", Res) << std::endl;
       lst.push_back(Res);

       dom_power(Res, Gy, l, QD); 		// Gy^l mod Q
       lst.push_back(Res);
       QD.write(std::cout << "(Y)^" << l << ": ", Res) << std::endl;

       l = power^2;
       dom_power(Res, G, l, QD); lst.push_back(Res);
       QD.write(std::cout << "(X)^" << l << ": ", Res) << std::endl;
       dom_power(Res, Gy, l, QD);  lst.push_back(Res);
       QD.write(std::cout << "(Y)^" << l << ": ", Res) << std::endl;


       std::cout<<"_________________________________"<< std::endl;
       return lst;
}

Field::Element mathS::ComputeQModL(Integer q, Integer l)
{
    Field _temp(l);
    Field::Element elem;
    _temp.init(elem,q);
    return elem;
}

std::list<Bivariates::Element> mathS::ComputeNotQ(Field::Element el, Curve c)
{
    Field _temp = c.CurveField;
    Polys PZp(_temp,Indeter("X"));
    Bivariates PPZp(PZp,Indeter("Y"));
    Field::Element temp,temp2;
    temp = el;


    Bivariates::Element _polyx;
    PPZp.init(_polyx,Degree(0),0);
    Polys::Element _x;
    PZp.init(_x,Degree(1));
    PZp.assign(_polyx[0],_x);
    PPZp.write(std::cout<<_polyx<<std::endl);

    Bivariates::Element x, y,q,tq,qm1,qp1,tempb;
    q = mathS::CreatePolynomial(temp,c);
    _temp.add(temp2,temp,2);
    tq = mathS::CreatePolynomial(temp2,c);
    _temp.init(temp2,temp);
    _temp.subin(temp2,1);
    qm1 = mathS::CreatePolynomial(temp2,c);
    _temp.init(temp2,temp);
    _temp.addin(temp2,1);
    qp1 = mathS::CreatePolynomial(temp2,c);

    PPZp.init(tempb,Degree(0),2);
    PPZp.write(std::cout<<"Div 2 pol"<<tempb<<std::endl);


    PPZp.mul(x,qm1,qp1);
    PPZp.divin(x,q);
    PPZp.divin(x,q);
    PPZp.subin(_polyx,x);
    x = _polyx;

    PPZp.div(y,tq,tempb);
    PPZp.divin(y,q);
    PPZp.divin(y,q);
    PPZp.divin(y,q);
    PPZp.divin(y,q);


    std::list<Bivariates::Element> lst;
    lst.push_back(x);
    lst.push_back(y);

    return lst;


}
//rename
Bivariates::Element getListElement(std::list<Bivariates::Element> lst, int element)
{
    int counter = 0;
    Bivariates::Element elem;
    for (std::list<Bivariates::Element>::iterator it = lst.begin(); it != lst.end(); it++)
       {
         if (counter == element)
         {
             elem = *it;
             return elem;
         }
         counter ++;
       }
    printer::Print(1,"Not found");
    return -1;
}

std::list<Bivariates::Element> PolynomAddition(std::list<Bivariates::Element> lstSq, std::list<Bivariates::Element> listA, Curve c)
{
    Modular<Integer> Zp = c.CurveField;
    Polys inst( Zp, Indeter("X") );
    Bivariates  field( inst, Indeter("Y") );

    Bivariates::Element tempxp = getListElement(lstSq,0);
    Bivariates::Element tempyp = getListElement(lstSq,1);
    Bivariates::Element tempxq = getListElement(listA,0);
    Bivariates::Element tempyq = getListElement(listA,1);
    Bivariates::Element x,y,lambda,temp;

    if (tempxp == tempxq && tempyp == tempyq)
    {
        field.init(lambda);
        field.sub(lambda,tempyq,tempyp);
        field.sub(temp,tempxq,tempxp);
        field.divin(lambda,temp);

    }

    else
    {
        Polys p;
        p = inst;
        field.init(temp,Degree(0));
        p.assign(temp[0],Integer(3));
        field.write(std::cout<<temp<<std::endl);
        lambda = tempxp;
        field.mulin(lambda,tempxp);
        field.mulin(lambda,temp);

        field.init(temp,Degree(0));
        p.assign(temp[0],c.a4);
        field.addin(lambda,temp);
        field.divin(lambda,tempyp);

        field.init(temp,Degree(0));
        p.assign(temp[0],Integer(2));

        field.divin(lambda,temp);

    }
    x = lambda;
    field.mulin(x,lambda);
    field.subin(x,tempxp);
    field.subin(x,tempxq);

    field.sub(y,tempxp,x);
    field.mulin(y,lambda);
    field.subin(y,tempyp);

    std::list<Bivariates::Element> result;
    result.push_back(x);
    result.push_back(y);

    return result;
}

Integer ComputeLastStep(std::list<Bivariates::Element> lstSq, std::list<Bivariates::Element> listA, Curve c, Integer qbar)
{
   Integer t;
   Bivariates::Element tempx = getListElement(lstSq,0);
   Bivariates::Element tempy = getListElement(lstSq,1);
   Bivariates::Element xp,yp,txp,typ;


   for (t = Integer(1); t<qbar; t++)
   {

       if (tempx==txp)
       {
           if (tempy == typ)
           {
               return t;
           }
       }

       //CHANGE!!
        PolynomAddition(lstSq,listA,c);
   }

}

void mathS::SchoffsAlgorithm(Integer q, Curve c)
{
    std::vector<Integer> primeNumbers = mathS::ComputePrimeNumbers(q);//+

    int length = primeNumbers.size();
    Integer PreChinese[length][2] ;
    Integer counter = 0;
    for (Integer i = 5; i!=6; i++)
    {
        std::cout<<"For number" <<i<<std::endl;
        Bivariates::Element divisionPol;
        divisionPol = mathS::CreatePolynomial(i,c);



        Field::Element el;
        el = mathS::ComputeQModL(q,i);

        std::list<Bivariates::Element> XYBarPolynomList;
        XYBarPolynomList = mathS::ComputeNotQ(el,c);

        std::list<Bivariates::Element> XYPPolynomList;
        XYPPolynomList = mathS::RingTest(c,divisionPol,i);


         std::list<Bivariates::Element> FinalPolynom;
         FinalPolynom = PolynomAddition(XYPPolynomList, XYBarPolynomList ,c);
         PreChinese[counter][0] = ComputeLastStep(FinalPolynom,XYPPolynomList,c,q);
         PreChinese[counter][1] = i;
         std::cout<<"Result"<< PreChinese[counter][0]<<std::endl;
         std::cout<< PreChinese[counter][1]<<std::endl;


    }

}
