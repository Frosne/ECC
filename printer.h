#ifndef PRINTER_H
#define PRINTER_H

#include <point.h>
#include <curve.h>
#include <phopoint.h>

#include <string.h>
#include <string>

class printer
{
public:
    bool isWarning = false;
    printer();
    void static Print();
    void static Print(bool isWarning, std::string info);
    void static PrintCurve(Curve c);
    void static PrintPoint(Point p);
    void static Print(std::string info);
    void static PrintRhoPoint(PhoPoint p);
};

#endif // PRINTER_H
