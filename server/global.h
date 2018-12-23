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

void checkSharedFiles();
void checkSharedFileRemoval();
void checkSeeders();
vector<string> getSeederlist();
void createLog() ;
void log(const char *msg) ;
int createSocket() ;
void addseed(const char *msg) ;
void connectClients(int socketId);
vector<URL> getInMemorySeederlist(string filename) ;
vector<URL> getSeederlistFromStorage(string filename) ;
void removeFromSeederlist(string content) ;
string getToken(string &data,string delimeter) ;
void trackfile(string file);
void removefile(string file) ;
string getFilename(string &file) ;
void printSeederlist();

#endif