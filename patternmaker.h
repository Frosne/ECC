#ifndef PATTERNMAKER_H
#define PATTERNMAKER_H

#include <string>
#include <list>
#include <curve.h>
#include <point.h>

#include <givaro/givinteger.h>

class PatternMaker
{
public:
    std::list<int> types;
    int length;
    std::string pattern;
    PatternMaker();
    PatternMaker(std::string pattern);
    static std::string Resign(std::string text);
    void parse(Curve c, Point y, Point p, Point q);
    std::string ReturnPattern();
    std::string static ToString(int number);
};

#endif // PATTERNMAKER_H
