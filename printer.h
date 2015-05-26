#ifndef PRINTER_H
#define PRINTER_H

#include <point.h>
#include <curve.h>

#include <string.h>
#include <string>

class printer
{
public:
    bool isWarning = false;
    printer();
    void static Print();
    void static Print(bool isWarning, std::string info);
    void static PrintCurve(Curve c1);
    void static PrintPoint(Point p1);
    void static Print(std::string info);
};

#endif // PRINTER_H
