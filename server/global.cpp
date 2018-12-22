#include "global.h"

URL tracker1;
URL tracker2;
string log_filename;
string seeder_file;
map<string, vector<URL>> seederlist;

fstream file;
fstream seederfile;

string getFilename(string s) ;

void createLog()
{
    file.open(log_filename, ios::out);
    seederfile.open(seeder_file, ios::out);
}

void log(const char *msg)
{
    if (file.is_open())
    {
        file << msg << endl;
    }
}

void trackfile(string file)
{
    string delimeter = "\n";
    string filename;
    size_t pos = 0;
    if ((pos = file.find(delimeter)) != string::npos)
    {
        filename = file.substr(0, pos);
        file.erase(0, pos + delimeter.length());
    }
    string hashString;
    if ((pos = file.find(delimeter)) != string::npos)
    {
        hashString = file.substr(0, pos);
        file.erase(0, pos + delimeter.length());
    }
    string ip;
    delimeter = ":";
    if ((pos = file.find(delimeter)) != string::npos)
    {
        ip = file.substr(0, pos);
        file.erase(0, pos + delimeter.length());
    }
    int port;
    stringstream strValue;
    strValue << file;
    strValue >> port;
    string key = getFilename(filename) + hashString;
    URL url;
    url.ip = ip;
    url.port = port;
    seederlist[key].push_back(url);
    if (seederfile.is_open())
    {
        seederfile << key << "=" << url.ip << ":" << url.port << endl;
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
        int readval = recv(acc, buffer2, 1024, 0);
        msg = "received: " + string(buffer2);
        log(msg.c_str());
        trackfile(string(buffer2));
        strcpy(buffer1, "share file tracked");
        msg = "sending: " + string(buffer1);
        log(msg.c_str());
        readval = send(acc, buffer1, strlen(buffer1), 0);
    }
}
string getFilename(string s) {
   char sep = '/';
   size_t i = s.rfind(sep, s.length());
   if (i != string::npos) {
      return(s.substr(i+1, s.length() - i));
   }

   return("");
}