#include "header.h"
#ifndef Global_H
#define Global_H

#define PEERS 10
#define CHUNK_SIZE 512*1024 
#define MAX 10000

using namespace std;

struct URL{
    string ip;
    int port ;
} ;

struct metafile{
    struct URL url1,url2 ;
    string filename ;
    int filesize ;
    string hash ;
} ;

extern URL client ;
extern URL tracker1;
extern URL tracker2;
extern string log_filename;

void createLog() ;
void log(char *msg) ;
int createSocket() ;
void connectPeers(int socketId);
string hashFile(unsigned char *file, size_t size);
vector<string> createHashString(char * filename);
void saveTorrentFile(char *filename,URL url1,URL url2);
void shareFile(struct metafile mtorrent);


#endif