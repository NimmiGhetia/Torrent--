#include "global.h"

void shareFile(struct metafile mtorrent)
{
    createLog();
    int socketId=createSocket() ;
    connectPeers(socketId);
}