#include "global.h"

void shareFile(struct metafile mtorrent)
{
    string filepath;
    cin >> filepath;
    string filename;
    cin >> filename;
    cout << "inside share file";
    struct stat thestat;
    string fullname=filepath+"/"+filename ;
    // cout << filepath << " " << filename;
    cout<<fullname ;
    struct metafile mtorrentfile=saveTorrentFile((char *)fullname.c_str(), tracker1, tracker2);
    createLog();
    int socketId = createSocket();
    connectPeers(socketId,mtorrentfile);
}