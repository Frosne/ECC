#include "patternmaker.h"
#include "string"
#include "point.h"
#include "curve.h"
#include <iostream>
#include <printer.h>
#include <list>


using namespace std;

PatternMaker::PatternMaker()
{


}

PatternMaker:: PatternMaker(std::string pattern)
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
    std::string pattPart = "Y = Y + ";
    size_t t = task.find(pattPart)+pattPart.length();
    if (t>=0)
    {
        std::string symbol = PatternMaker::Resign(task.substr(t));

        if (symbol == "P")
        {
            return 1;
        }
        else if (symbol == "Q")
            return 2;
        else if (symbol == "Y")
            return 3;


    }
    else
    {
       printer::Print(1,"Pattern is not recognizable");
       return -1;
    }

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

std::string PatternMaker::Resign(std::string text)
{
   std::string _text =  ResignL(text);
   return ResignR(_text);

}

void PatternMaker::parse(Curve c, Point y, Point p, Point q)
{
  int type=0;
  int length = 0;
  length = searchPattern(this->pattern, type);
  this->length = length;

  size_t t = -1;
  t =  this->pattern.find(";")+sizeof(char)*1;

  for (int i = 0; i<length; i++)
  {
      size_t second = -1;
      second =  this->pattern.find(";",t);
      int _type = getOperation(PatternMaker::Resign(this->pattern.substr(t,second-t)));
      types.push_front(_type);
      t = second+1;
  }
}

std::string PatternMaker::ToString(int number)
{

    std::string result =  std::to_string(number);
    return result;
}

int getListElement(list<int> lst, int element)
{
    list<int> temp = lst;
    int it = 0;

    list<int>::iterator i;
    if (lst.size() <element)
        return -1;
    for(i=temp.begin(); i != temp.end(); i++)
    {
        if (it==element)
        {
            return *i;
        }

    }

    return -1;
}

std::string PatternMaker::ReturnPattern()
{

    std::string result = std::to_string(this->length);
    for (int i = 0; i<this->length-1; i++)
    {
        result = result+ "  " + std::to_string(getListElement(this->types,i));
    }

    return result;
}
