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
    string name = getFilename(filename);
    // string key = getFilename(filename) + hashString;
    URL url;
    url.ip = ip;
    url.port = port;
    vector<string> hashstr;
    int pos = 0;
    int next = 40;
    string sub = hashString.substr(pos, next);
    pos += next;
    while (pos <= hashString.length())
    {
        stringstream ss;
        ss << name;
        ss << sub;
        hashstr.push_back(ss.str());
        sub = hashString.substr(pos, next);
        pos += next;
        seederlist[ss.str()].push_back(url);
        stringstream ss1;
        ss1 << ss.str() << "=" << url.ip << ":" << url.port << " " << endl;
        addseed(ss1.str().c_str());
    }
}

void removefile(string file)
{
    string filecontent = getToken(file, "\n");
    while (filecontent.length() > 0)
    {
        removeFromSeederlist(filecontent);
        filecontent = getToken(file, "\n");
    }
}

string getPeers(string file)
{
    cout<<"inside get peers" ;
        vector<URL> urls = getInMemorySeederlist(file);
        string result = "";
        for (int i = 0; i < urls.size(); i++)
        {
            stringstream ss;
            ss << urls[i].ip << ":" << urls[i].port << endl;
            result += ss.str();
        }
        return result ;
}