#include "global.h"
void communicate(int accid);
void checkRequests()
{
    int socketId = createSocketForClient();
    while (1)
    {
        int accId = acceptClients(socketId);
        if (accId > 0)
        {
            communicate( accId);
            printSeederlist();
            close(accId) ;
        }
    }
}

void communicate(int accId)
{
        string buffer = receiveRemote(accId);
        string buffer2 = performAction(buffer);
        sendRemote(accId, string(buffer2));
}