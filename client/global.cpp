#include "global.h"

URL client;
URL tracker1;
URL tracker2;

int socketId ;
map<string,string> fileAddress ;
map<string,string> mtorrentAddress ;

string getToken(string &str, string delimeter)
{
    string token;
    size_t pos = 0;
    if ((pos = str.find(delimeter)) != string::npos)
    {
        token = str.substr(0, pos);
        str.erase(0, pos + delimeter.length());
    }
    return token;
}

int createSocketForClient()
{
    URL url = client;
    int socketId ;
    if ((socketId = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        log(string("socket failed:" + errno).c_str());
        exit(EXIT_FAILURE);
    }
    log("socket created for peer");
    const int trueFlag = 1;
    if (setsockopt(socketId, SOL_SOCKET, SO_REUSEADDR, &trueFlag, sizeof(int)) < 0)
        log("Failure");
    int opt = 1;
    struct sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = inet_addr(url.ip.c_str());
    localaddr.sin_port = url.port;
    if (bind(socketId, (struct sockaddr *)&localaddr, sizeof(localaddr)) < 0)
    {
        string msg = "bind failed:" + errno;
        cout << endl
             << errno << endl;
        log(msg.c_str());
        exit(EXIT_FAILURE);
    }
    string msg = "binding to " + url.ip + ":";
    msg += to_string(url.port);

    if (listen(socketId, CLIENT) == 0)
        log("listening..");

    return socketId;
}

int acceptClient(int socketId)
{
    struct sockaddr_in clientaddr;
    socklen_t addr_size;
    addr_size = sizeof(struct sockaddr_in);
    int acc = accept(socketId, (struct sockaddr *)&clientaddr, &addr_size);
    if (acc == 0)
    {
        log("not connected");
    }
    else
    {
        URL client;
        client.port = ntohs(clientaddr.sin_port);
        stringstream s;
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientaddr.sin_addr), ip, INET_ADDRSTRLEN);
        string msg = "connection established to " + string(ip) + ":";
        msg += to_string(client.port);
        log(msg.c_str());
    }
    return acc;
}

int createSocketForTracker()
{
    URL url = client;
    // int socketId;
    if ((socketId = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        log(string("socket failed:" + errno).c_str());
        exit(EXIT_FAILURE);
    }
    log("socket created");
    const int trueFlag = 1;
    if (setsockopt(socketId, SOL_SOCKET, SO_REUSEADDR, &trueFlag, sizeof(int)) < 0)
        log("Failure");
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

void connectPeers(int socketId,URL peer)
{
    URL url = peer;
    struct sockaddr_in peeraddr;
    peeraddr.sin_family = AF_INET;
    peeraddr.sin_addr.s_addr = inet_addr(url.ip.c_str());
    peeraddr.sin_port = url.port;
    socklen_t addr_size;
    addr_size = sizeof(struct sockaddr_in);
    if (connect(socketId, (struct sockaddr *)&peeraddr, sizeof(peeraddr)) < 0)
    {
        stringstream ss ;
        ss<<"could not connect to "<<peer.ip<<":"<<peer.port ;
        string msg=ss.str() ;
        log(msg.c_str());
        exit(1);
    }

}

void sendRemote(int socketId,string data)
{
    stringstream ss ;
    ss<<"sending "<<string(data).length() <<" bytes" ;
    string msg = ss.str();
    log(msg.c_str());
    int readval = send(socketId, data.c_str(), 256, 0);
    if (readval < 0)
    {
        string msg = "error sending data";
        log(msg.c_str());
    }

}

int getSocketId()
{
    return socketId ;
}

string receiveRemote(int socketId)
{
    char buffer[1024] = {0};
    bzero(buffer, 1024);
    int valread = read(socketId, buffer, 1024);
    stringstream ss ;
    ss<<"received: " << string(buffer).length() << "bytes";
    string msg = ss.str() ;
    log(msg.c_str());
    // close(socketId) ;
    return string(buffer);
}

string getFilename(string &s)
{
    string temp = s;
    char sep = '/';
    size_t i = s.rfind(sep, s.length());
    if (i != string::npos)
    {
        return (s.substr(i + 1, s.length() - i));
    }
    s = temp.substr(0, s.substr(i + 1, s.length() - i).length());
    return ("");
}
