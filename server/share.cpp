#include "global.h"

void checkSharedFiles()
{
    createLog();
    int socketId=createSocket();
    while(1)
    {
        connectClients(socketId);
    }
}