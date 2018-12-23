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
    string tracker1_str = argv[1];
    string tracker2_str = argv[2];
    seeder_file = argv[3];
    log_filename = argv[4];

    tracker1 = processArgv(tracker1_str);
    tracker2 = processArgv(tracker2_str);
    thread first(checkSharedFiles);
    // thread second(checkSeeders);
    
    first.join();
    // second.join() ;
    return 0;
}