#include "global.h"

vector<string> hashFile(char *file)
{
    int pieces = ceil(strlen(file) / CHUNK_SIZE);
    vector<string> hash;
    for (int i = 0; i < pieces; i++)
    {
        unsigned char ibuf[CHUNK_SIZE];
        strncpy((char *)ibuf, file,512);
        file += 512 * sizeof(char);
        unsigned char obuf[20];
        SHA1(ibuf, strlen((char *)ibuf), obuf);
        hash.push_back(string((char *)obuf));
    }
    return hash;
}