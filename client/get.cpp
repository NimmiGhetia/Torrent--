#include "global.h"

void getDetailsFromTorrentFile(string path)
{
    struct metafile mtorrent;
    mtorrent = getTorrentFile(path);
    cout << "after get";
    int pos = 0;
    string name = getFilename(mtorrent.filename);
    string hashString = mtorrent.hash;
    vector<string> hashstr;
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
    }
    printf("strings");
    for (int i = 0; i < hashstr.size(); i++)
        cout << hashstr[i] << endl;
}

void getPeersFromTracker(string key)
{
    int socketId=getSocketId() ;
    sendRemote(socketId,key) ;
}