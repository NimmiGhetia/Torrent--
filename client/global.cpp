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
    URL url = tracker1;
    int socketId;
    if ((socketId = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        log(string("socket failed:" + errno).c_str());
        exit(EXIT_FAILURE);
    }
    log("socket created");
    // struct sockaddr_in localaddr;
    // localaddr.sin_family = AF_INET;
    // localaddr.sin_addr.s_addr = inet_addr(url.ip.c_str());
    // localaddr.sin_port = url.port;
    // cout << url.ip << ":" << url.port;
    // cout << socketId;
    // if (bind(socketId, (struct sockaddr *)&localaddr, sizeof(localaddr)) < 0)
    // {
    //     string msg = "bind failed:" + errno;
    //     cout << endl
    //          << errno << endl;
    //     log(msg.c_str());
    //     exit(EXIT_FAILURE);
    // }

    // if (listen(socketId, PEERS) == 0)
    //     log("listening..");

    return socketId;
}

void connectPeers(int socketId)
{
    URL url=tracker1 ;
    struct sockaddr_in peeraddr;
    peeraddr.sin_family = AF_INET;
    peeraddr.sin_addr.s_addr = inet_addr(url.ip.c_str());
    peeraddr.sin_port = url.port;
    socklen_t addr_size;
    addr_size = sizeof(struct sockaddr_in);
    printf("inside connectclient");
    cout<<"tracker 1:"<<url.ip<<":"<<url.port ;
    if (connect(socketId, (struct sockaddr *)&peeraddr, sizeof(peeraddr)) < 0)
    {
        string msg = "could not connect";
        log(msg.c_str());
        exit(1);
    }
    stringstream ss;
    ss << "GET /3/movie/" << 550 << "?api_key=xxx HTTP/1.1\r\n"
       << "Host: api.themoviedb.org\r\n"
       << "Accept: application/json\r\n"
       << "\r\n\r\n";
    
    string request = ss.str();
    if (send(socketId, request.c_str(), request.length(), 0) != (int)request.length())
    {
        string msg="error sending data" ;
        log(msg.c_str());
        exit(1);
    }
}