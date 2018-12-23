#include "global.h"

void shareFile(struct metafile mtorrentfile)
{
    string filepath;
    cin >> filepath;
    string filename;
    cin >> filename;
    string fullname = filepath + "/" + filename;
    struct metafile mtorrent = saveTorrentFile((char *)fullname.c_str(), tracker1, tracker2);
    int socketId = createSocket();
    stringstream ss;
    ss << "share\n" ;
    ss << mtorrent.filename <<"\n";
    ss << mtorrent.hash << "\n";
    ss << client.ip << ":" << client.port;
    string buffer1 = ss.str();
    // cout<<"printinf details"<<mtorrent.filename<<" "<<mtorrent.hash<<""<<buffer1 ;
    connectPeers(socketId);
    sendRemote(socketId,buffer1);
}