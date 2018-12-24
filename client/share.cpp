#include "global.h"

void waitForUpload() ;
string findPart(string hashkey) ;

void shareFile(string filename,string filepath)
{
    string fullname = filepath + "/" + filename;
    struct metafile mtorrent = saveTorrentFile((char *)fullname.c_str(), tracker1, tracker2);
    stringstream ss;
    ss << "share\n" ;
    ss << mtorrent.filename <<"\n";
    ss << mtorrent.hash << "\n";
    ss << client.ip << ":" << client.port;
    string buffer1 = ss.str();
    int socketId = createSocketForTracker();
    connectPeers(socketId,tracker1);
    sendRemote(socketId,buffer1);
    string buffer=receiveRemote(socketId) ;
    cout << "file shared successfully";
    fflush(stdin) ;
    waitForUpload() ;
}

void waitForUpload()
{
    int socketId=createSocketForClient() ;
    int acc=acceptClient(socketId) ;
    if(acc>0)
    {
        string hashkey=receiveRemote(acc) ;
        string buffer=findPart(hashkey) ;
    }
}

string findPart(string hashkey)
{
    string filename=hashkey.substr(0,hashkey.length()-20) ;
    cout<<filename ;
    return "" ;
}