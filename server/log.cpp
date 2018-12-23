#include "global.h"

fstream file;
fstream seederfile;

void createLog()
{
    file.open(log_filename, ios::out|ios::ate);
    seederfile.open(seeder_file, ios::out);
}

void log(const char *msg)
{
    if (file.is_open())
    {
        file << msg << endl;
    }
}

void addseed(const char *msg)
{
    if (seederfile.is_open())
    {
        seederfile << msg << endl;
    }
}
