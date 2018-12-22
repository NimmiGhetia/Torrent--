#include "global.h"

void checkSharedFiles()
{
    createLog();
    int socketId=createSocket();
    int i=0;
    while(1)
    {
        i++ ;
        connectClients(socketId);
    }
}