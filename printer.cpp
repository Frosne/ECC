#include "printer.h"
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

void  printer::PrintCurve(Curve c1)
{
    std::cout<<"Curve Info: "<< "E: y^2 + " <<c1.a1 <<"xy + "<<c1.a3 <<"y = x^3 + " << c1.a2<< "x^2 + " <<c1.a4<<"x + " <<c1.a6 <<std::endl;
    std::cout<<"Curve Info: "<< "Curve Order: "<< c1.order<< "; Curve Diskriminant: " << c1.diskriminant << std::endl;
}

void  printer::PrintPoint(Point p1)
{
    std::cout<<"Point info: "<< "X:" << p1.x1 << " Y:"<< p1.y1<<std::endl;
}

void printer::Print(std::string info)
{
    printer::Print(0,info);
}


