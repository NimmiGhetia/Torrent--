#include "global.h"

string toHash(unsigned char *hash)
{
    if (hash == NULL)
    {
        printf("HASH NULL\n");
        return "";
    }
    unsigned char buf[40];
    for (int i = 0; i < 20; i++)
    {
        sprintf((char *)&(buf[i * 2]), "%02x", hash[i]);
    }
    return string((char *)buf);
}

string hashFile(unsigned char *file,size_t size)
{
    string buf="";
    unsigned char obuf[20];
    SHA1(file, size, obuf);
    buf = toHash(obuf);
    return buf;
}