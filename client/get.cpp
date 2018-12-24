#include "global.h"

void downloadFrom(URL peer,string hashkey)
{
    int socketId=createSocketForTracker();
    connectPeers(socketId,peer) ;
    string rcv=receiveRemote(socketId) ;
    cout<<peer.ip<<":"<<peer.port ;
}

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
    {
        cout << hashstr[i] << endl;
        vector<URL> peers = getPeersFromTracker(hashstr[i].c_str());
        int sz = peers.size();
        int randomIndex = rand() % sz;
        stringstream ss;
        ss << peers[randomIndex].ip << ":" << peers[randomIndex].port << "\n"
           << hashstr[i];
            string str =ss.str() ;
        thread t(&downloadFrom, peers[randomIndex], str);
        t.join();
    }
}

vector<URL> getPeersFromTracker(string key)
{
    int socketId = createSocketForTracker();
    connectPeers(socketId, tracker1);
    key = "get\n" + key;
    sendRemote(socketId, key);
    string buffer;
    buffer = receiveRemote(socketId);
    vector<URL> urls;
    string s;
    while ((s = getToken(buffer, "\n")).length() > 0)
    {
        URL url;
        string ip = getToken(s, ":");
        url.ip = ip;
        stringstream ss;
        ss << s;
        int port;
        ss >> port;
        url.port = port;
        urls.push_back(url);
    }
    printf("printing urls..\n");
    for (int i = 0; i < urls.size(); i++)
        cout << urls[i].ip << ":" << urls[i].port << endl;
    return urls;
}

