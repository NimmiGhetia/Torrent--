#include "global.h"

URL processArgv(string source)
{
    URL url;
    string delimeter = ":";
    string ip;
    size_t pos = 0;
    if ((pos = source.find(delimeter)) != string::npos)
    {
        ip = source.substr(0, pos);
        source.erase(0, pos + delimeter.length());
    }
    int port;
    stringstream strValue;
    strValue << source;
    strValue >> port;
    url.ip = ip;
    url.port = port;
    return url;
}

int main(int argc, char *argv[])
{
    string command = argv[0];
    cout << "inside ./client";
    string client_str = argv[1];
    string tracker1_str = argv[2];
    string tracker2_str = argv[3];
    client = processArgv(client_str);
    tracker1 = processArgv(tracker1_str);
    tracker2 = processArgv(tracker2_str);
    log_filename = argv[4];
    createLog();

    enterCommand() ;

    return 0;
}