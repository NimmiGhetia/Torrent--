#include "global.h"

URL tracker1;
URL tracker2;
string log_filename;
string seeder_file;
map<string, vector<URL>> seederlist;

char *performAction(string msg, string buffer2);

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

void connectClients(int socketId)
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
        char buffer1[256], buffer2[1024];
        bzero(buffer2, 1024);
        bzero(buffer1, 256);
        int readval = recv(acc, buffer2, 1024, 0);
        msg = "received: " + string(buffer2);
        log(msg.c_str());
        char *buffer = performAction(msg, string(buffer2));
    }
}

char *performAction(string msg, string buffer2)
{
    char buffer1[1024];
    string doaction = getToken(buffer2, "\n");
    if (strcmp(doaction.c_str(), "share") == 0)
    {
        trackfile(buffer2);
        printSeederlist() ;
        strcpy(buffer1, "file shared successfully");
    }
    else if (strcmp(doaction.c_str(), "remove") == 0)
    {
        removefile(buffer2);
        printSeederlist();
        strcpy(buffer1, "file removed successfully");
    }
    strcpy(buffer1, "default");
    return buffer1;
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