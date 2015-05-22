#ifndef SEARCHOUTPUT_H
#define SEARCHOUTPUT_H

#include <givaro/givinteger.h>

class SearchOutput
{
public:
    SearchOutput();
    SearchOutput(int position, bool direction);
        Givaro::Integer position;
        bool direction;

};

#endif // SEARCHOUTPUT_H
