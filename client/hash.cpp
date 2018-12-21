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

string hashFile(unsigned char *file)
{
    string buf="";
    // printf("inside for");
    unsigned char obuf[20];
    cout << file;
    unsigned char ibuf[]="A" ;
    SHA1(ibuf, sizeof(file), obuf);
    cout<<".......\n"<<ibuf;
    for (int i = 0; i < 20; i++) {
        printf("%02x ", obuf[i]);
    }
    cout<<".........\n";
    // cout << toHash(obuf);
    buf = toHash(obuf);
    return buf;
}