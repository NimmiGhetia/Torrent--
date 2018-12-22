#include "global.h"

URL client;
URL tracker1;
URL tracker2;
string log_filename;

fstream file;
void createLog()
{
    file.open(log_filename, ios::out);
}
void log(const char *msg)
{
    if (file.is_open())
    {
        file << msg << endl;
    }
}

int createSocket()
{
    URL url = client;
    int socketId;
    if ((socketId = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        log(string("socket failed:" + errno).c_str());
        exit(EXIT_FAILURE);
    }
    log("socket created");
    struct sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = inet_addr(url.ip.c_str());
    localaddr.sin_port = url.port;
    if (bind(socketId, (struct sockaddr *)&localaddr, sizeof(struct sockaddr_in)) == 0)
    {
        string msg = "binding to " + client.ip + ":";
        msg += to_string(client.port);
        log(msg.c_str());
    }
    else
        log("Unable to bind");
    return socketId;
}

void connectPeers(int socketId, struct metafile mtorrent)
{
    URL url = tracker1;
    struct sockaddr_in peeraddr;
    peeraddr.sin_family = AF_INET;
    peeraddr.sin_addr.s_addr = inet_addr(url.ip.c_str());
    peeraddr.sin_port = url.port;
    socklen_t addr_size;
    addr_size = sizeof(struct sockaddr_in);
    if (connect(socketId, (struct sockaddr *)&peeraddr, sizeof(peeraddr)) < 0)
    {
        string msg = "could not connect";
        log(msg.c_str());
        exit(1);
    }
    stringstream ss;
    ss << mtorrent.filename << endl;
    ss << mtorrent.hash << endl;
    ss << client.ip <<":"<<client.port ;
    string buffer1=ss.str();
    string msg = "sending: " + string(buffer1);
    log(msg.c_str());

    int readval = send(socketId, buffer1.c_str(), 256, 0);
    if (readval < 0)
    {
        string msg = "error sending data";
        log(msg.c_str());
        exit(1);
    }
    char buffer[1024] = {0};
    bzero(buffer, 1024);
    int valread = read(socketId, buffer, 1024);
    msg = "received: " + string(buffer);
    log(msg.c_str());
}
