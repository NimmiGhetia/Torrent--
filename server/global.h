#include "header.h"
#ifndef Global_H
#define Global_H

struct URL{
    string ip;
    int port ;
} ;

struct metafile{
    struct URL url1,url2 ;
    string filename ;
    int filesize ;
    char * hash ;
} ;

extern map<string,vector<URL>> seederlist;
extern URL tracker1;
extern URL tracker2;
extern string log_filename;
extern string seeder_file;

void checkRequests();
void checkSharedFileRemoval();

void checkSeeders();
vector<string> getSeederlist();
void addseed(const char *msg) ;
vector<URL> getInMemorySeederlist(string filename) ;
vector<URL> getSeederlistFromStorage(string filename) ;
void removeFromSeederlist(string content) ;
void printSeederlist();

void createLog() ;
void log(const char *msg) ;
int createSocket() ;
int getSocketId() ;
int acceptClients(int socketId);
string receiveRemote(int socketId) ;
void sendRemote(int socketId,string data) ;
string performAction(string data) ;


string getToken(string &data,string delimeter) ;
string getFilename(string &file) ;

void trackfile(string file);
void removefile(string file) ;
string getPeers(string file);

#endif