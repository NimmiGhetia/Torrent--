#include "header.h"
#ifndef Global_H
#define Global_H

#define PEERS 10
#define CHUNK_SIZE 512 * 1024
#define MAX 10000
#define setcursor(x, y) printf("\033[%d;%dH", x, y);
#define cursorup(x) printf("\033[%dA", (x))
#define cursordown(x) printf("\033[%dB", (x))
#define cursorforward(x) printf("\033[%dC", (x))
#define cursorbackward(x) printf("\033[%dD", (x))
#define clearscreen() printf("\033[H\033[J")

#define KEY_ESCAPE 0x001b
#define KEY_ENTER 0x000a
#define KEY_UP 0x0105
#define KEY_DOWN 0x0106
#define KEY_LEFT 0x0107
#define KEY_RIGHT 0x0108
#define CLIENT 5
using namespace std;

struct URL
{
    string ip;
    int port;
};

struct metafile
{
    struct URL url1, url2;
    string filename;
    int filesize;
    string hash;
};

extern URL client;
extern URL tracker1;
extern URL tracker2;
extern string log_filename;
extern map<string,string> fileAddress ;
extern map<string,string> mtorrentAddress ;

void createLog();
void log(const char *msg);

int createSocketForClient();
int createSocketForTracker();
void connectPeers(int socketId, URL peer);
int acceptClient(int socketId);
void sendRemote(int sock, string data);
string receiveRemote(int sock);
int getSocketId();
void joinAllThreads() ;

string hashFile(unsigned char *file, size_t size);
vector<string> createHashString(char *filename);
struct metafile saveTorrentFile(const char *filename, URL url1, URL url2);
struct metafile getTorrentFile(string filename);
void getDetailsFromTorrentFile(string path);

void enterCommand();
string getToken(string &str, string delimeter);
void replaceExt(string &a, const string &b);
string getFilename(string &name);

void shareFile(string filename, string filepath);
void removeFile(string filename);

vector<URL> getPeersFromTracker(string key);
void getDetailsFromTorrentFile(string path);
void downloadFrom(URL peer,string hashkey);
#endif