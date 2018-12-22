#include "global.h"

URL processArgv(string source)
{
    URL url;
    string delimeter = ":";
    string ip;
    size_t pos = 0;
    // cout<<source ;
    if ((pos = source.find(delimeter)) != string::npos)
    {
        // cout<<"inside if";
        ip = source.substr(0, pos);
        source.erase(0, pos + delimeter.length());
    }
    cout << ip;
    int port;
    stringstream strValue;
    strValue << source;
    strValue >> port;
    cout << ":" << port;
    url.ip = ip;
    url.port = port;
    return url;
}

int main(int argc, char *argv[])
{
    string client_str = argv[1];
    string tracker1_str = argv[2];
    string tracker2_str = argv[3];
    client = processArgv(client_str);
    tracker1 = processArgv(tracker1_str);
    tracker2 = processArgv(tracker2_str);
    log_filename = argv[4];
    saveTorrentFile("temp.txt", tracker1, tracker2);
    return 0;
}