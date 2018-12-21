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

vector<string> hashFile(unsigned char *file);
void createTorrentFile(char * filename);

#endif