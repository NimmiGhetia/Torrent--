#include "global.h"

void trackfile(string file)
{
    string filename = getToken(file, "\n");
    string hashString = getToken(file, "\n");
    string ip = getToken(file, ":");
    int port;
    stringstream strValue;
    strValue << file;
    strValue >> port;
    string key = getFilename(filename) + hashString;
    URL url;
    url.ip = ip;
    url.port = port;
    seederlist[key].push_back(url);
    stringstream ss;
    ss << key << "=" << url.ip << ":" << url.port << " " << endl;
    addseed(ss.str().c_str());
}

void removefile(string file)
{
    string filecontent = getToken(file, "\n");
    while (filecontent.length() > 0)
    {
        removeFromSeederlist(filecontent);
        filecontent=getToken(file,"\n") ;
    }
}