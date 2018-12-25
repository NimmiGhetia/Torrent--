#include "global.h"

fstream file;
string log_filename ;

void createLog()
{
    file.open(log_filename, ios::app);
}

void log(const char *msg)
{
    if (file.is_open())
    {
        file << msg << endl;
    }
}

