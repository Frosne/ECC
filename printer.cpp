#include "printer.h"
#include "phopoint.h"
#include <iostream>


using namespace std;

printer::printer()
{
}

void printer::Print()
{
    //
}

void printer::Print(bool isWarning, std::string info)
{
    if (isWarning)
        std::cout<<"Warning!"<<info<<std::endl;
    else
        std::cout<<"Info!"<<info<<std::endl;
}

void  printer::PrintCurve(Curve c)
{
    std::cout<<"Curve Info: "<< "E: y^2 + " <<c.a1 <<"xy + "<<c.a3 <<"y = x^3 + " << c.a2<< "x^2 + " <<c.a4<<"x + " <<c.a6 <<std::endl;
    std::cout<<"Curve Info: "<< "Curve Order: "<< c.order<< "; Curve Diskriminant: " << c.diskriminant << std::endl;
}

void  printer::PrintPoint(Point p)
{
    std::cout<<"Point info: "<< "X:" << p.x1 << " Y:"<< p.y1<<std::endl;
}

void printer::Print(std::string info)
{
    printer::Print(0,info);
}

void printer::PrintRhoPoint(PhoPoint p)
{
      std::cout<<"RhoPoint info: "<< "X:" << p.p.x1 << " Y:"<<  p.p.y1 << " a:" << p.a << " b:" <<p.b<<std::endl;
}
