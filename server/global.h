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

#endif