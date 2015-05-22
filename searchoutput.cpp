#include "searchoutput.h"

SearchOutput::SearchOutput()
{
}

SearchOutput::SearchOutput(int position, bool direction)
{
    this->direction = direction;
    this->position = position;
}
