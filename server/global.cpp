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

void connectClients(int socketId)
{
    struct sockaddr_in clientaddr;
    socklen_t addr_size;
    addr_size = sizeof(struct sockaddr_in);
    printf("inside connectclient");
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
        char buffer1[256], buffer2[1024];
        bzero(buffer2, 1024);
        bzero(buffer1, 256);
        int readval = recv(acc, buffer2, 14, 0);
        msg="received: "+string(buffer2);
        log(msg.c_str());
        strcpy(buffer1, "Hello");
        msg="sending: "+string(buffer1) ;
        log(msg.c_str());
        readval = send(acc, buffer1, strlen(buffer1), 0);
    }
}