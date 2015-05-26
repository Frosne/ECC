#include "patternmaker.h"
#include "string"
#include "point.h"
#include "curve.h"
#include <iostream>
#include <printer.h>


patternMaker::patternMaker()
{


}

patternMaker:: patternMaker(std::string pattern)
{
    this->pattern = pattern;
}

int numberInterpretation(std::string number)
{
    if (number == "second")
        return 2;
    if (number == "fourth")
        return 4;
    if (number == "third")
        return 3;
}

int searchPattern(std::string text, int type)
{
   size_t t = -1;
   t =  text.find("every");
   if (t!=-1)
   {
      type = 1;
      size_t pos =  text.find(';',t);
      std::string num =  text.substr(t+sizeof(char)*6,pos-t-sizeof(char)*6);
      int number = numberInterpretation(num);
      return number;

   }

return -1;
}

int getOperation(std::string task)
{
    std::cout<<task<<std::endl;
   /* std::string pattPart = "Y = Y + ";
    size_t t = task.find(pattPart)+pattPart.length();
    if (t>=0)
    {
        std::string symbol = patternMaker::Resign(task.substr(t));
        std::cout<<symbol<<std::endl;
    }
    else
    {
       printer::Print(1,"Pattern is not recognizable");
       return -1;
    }
    */
    return -1;
}

std::string ResignL(std::string text)
{
    if (text.at(0)==' ')
      return ResignL(text.substr(1));
    else
        return text;
}

std::string ResignR(std::string text)
{
    if (text.at(text.length()-1)==' ')
       return ResignR(text.substr(0,text.length()-1));
    else
        return text;
}

std::string patternMaker::Resign(std::string text)
{
   std::string _text =  ResignL(text);
   return ResignR(_text);

}

void patternMaker::parse(Curve c, Point y, Point p, Point q)
{
  int type=0;
  int length = 0;
  length = searchPattern(this->pattern, type);

  size_t t = -1;
  t =  this->pattern.find(";")+sizeof(char)*1;

  for (int i = 0; i<length; i++)
  {
      size_t second = -1;
      second =  this->pattern.find(";",t);
      int _type = getOperation(patternMaker::Resign(this->pattern.substr(t,second-t)));
      types.push_back(_type);
      t = second+1;
  }
}
