#ifndef PATTERNMAKER_H
#define PATTERNMAKER_H

#include <string>
#include <list>
#include <curve.h>
#include <point.h>

class patternMaker
{
public:
    std::list<int> types;
    int length;
    std::string pattern;
    patternMaker();
    patternMaker(std::string pattern);
    static std::string Resign(std::string text);
    void parse(Curve c, Point y, Point p, Point q);
};

#endif // PATTERNMAKER_H
