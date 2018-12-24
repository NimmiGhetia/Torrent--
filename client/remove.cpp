#include "global.h"

void removeFile(string filename)
{

    stringstream ss;
    ss << "remove" << endl;
    string fname = filename;
    replaceExt(filename, "mtorrent");
    fstream file;
    file.open(filename, ios::in);
    if (file.is_open())
    {
        string line;
        getline(file, line);
        getline(file, line);
        getline(file, line);
        getline(file, line);
        int next = 40;
        string sub;
        int pos = 0;
        while (getline(file, line))
        {
            ss << fname;
            sub = line.substr(pos, next);
            if (sub.length() < 40 && sub.length() > 0)
            {
                next = next - sub.length();
                continue;
            }
            while (sub.length() == 40)
            {
                ss << sub;
                ss << "=";
                ss << client.ip << ":" << client.port;
                ss << endl;
                pos += next;
                if (line.length() == pos)
                    break;
                sub = line.substr(pos, next);
            }
            next = 20;
            pos = 0;
        }
    }
    if (remove(filename.c_str()) != 0)
    {
        log("error deleting file");
    }
    else
        log("file removed successfully");

    int socketId = createSocketForTracker();
    string buffer = ss.str().c_str();
    cout << buffer;
    connectPeers(socketId,tracker1);
    sendRemote(socketId,buffer) ;
}

vector<string> getHashStrings()
{
}