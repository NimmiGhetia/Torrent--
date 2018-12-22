#include "global.h"

extern URL tracker1;
extern URL tracker2;
extern string log_filename;

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
    struct sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = inet_addr(url.ip.c_str());
    localaddr.sin_port = url.port;
    cout << url.ip << ":" << url.port;
    cout << socketId;
    if (bind(socketId, (struct sockaddr *)&localaddr, sizeof(localaddr)) < 0)
    {
        string msg = "bind failed:" + errno;
        cout << endl
             << errno << endl;
        log(msg.c_str());
        exit(EXIT_FAILURE);
    }
    if (listen(socketId, CLIENT) == 0)
        log("listening..");

    return socketId;
}

void connectClients(int socketId)
{
    struct sockaddr_in clientaddr;
    socklen_t addr_size;
    addr_size = sizeof(struct sockaddr_in);
    printf("inside connectclient");
    int acc = accept(socketId, (struct sockaddr *)&clientaddr, &addr_size);
    if (acc = 0)
    {
        cout << "no connection";
    }
    else
    {
        cout << "connected";
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientaddr.sin_addr), ip, INET_ADDRSTRLEN);
        URL client;
        client.ip = ip;
        client.port = ntohs(clientaddr.sin_port);
        stringstream s;
        // string port;
        // s << client.port;
        // s >> port;

        string msg = "connection established to " + client.ip + ":" ;
        msg+=to_string(client.port);
        cout<<msg ;
        log(msg.c_str());
        char buffer1[256], buffer2[256];
        recv(acc, buffer2, 256, 0);
        cout << buffer2;
        strcpy(buffer1, "Hello");
        send(acc, buffer1, 256, 0);
    }
}