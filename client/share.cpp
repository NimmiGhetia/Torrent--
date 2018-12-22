#include "global.h"

void shareFile(struct metafile mtorrent)
{
    string filepath;
    cin >> filepath;
    string filename;
    cin >> filename;
    string fullname=filepath+"/"+filename ;
    struct metafile mtorrentfile=saveTorrentFile((char *)fullname.c_str(), tracker1, tracker2);
    int socketId = createSocket();
    connectPeers(socketId,mtorrentfile);
}