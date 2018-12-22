#include "global.h"

void checkSharedFiles()
{
    printf("inside checksharedfiles");
    createLog();
    int socketId=createSocket();
    int i=0;
    // while(i<10)
    // {
        i++ ;
        printf("checking") ;
        connectClients(socketId);
    // }
}