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
    string hash ;
} ;

string hashFile(unsigned char *file, size_t size);
vector<string> createHashString(char * filename);
void saveTorrentFile(char *filename,URL url1,URL url2);

#endif