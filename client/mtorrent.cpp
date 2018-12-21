#include "global.h"

void createTorrentFile(char *filename)
{
    ifstream file(filename, ios::binary);
    cout << "inside mtorrent";
    if (file.is_open())
    {
        cout << "inside if";
        constexpr size_t bufferSize = 1024 * 1024;
        unsigned char * buffer=NULL;
        while (file)
        {
            file.read((char *)buffer, bufferSize);
            vector<string> buf ;
            buf = hashFile(buffer);
            // cout<<(hashFile(buffer)).size() ;
            // for (auto i = hash.begin(); i != hash.end(); ++i)
            //     cout << *i << endl;
        }
        file.close();
        // cout << buf;
    }
}