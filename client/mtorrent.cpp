#include "global.h"

void createTorrentFile(char *filename)
{
    ifstream file;
    file.open(filename, ios::binary | ios::in);
    cout << "inside mtorrent";
    size_t bufferSize = CHUNK_SIZE;
    if (file.is_open())
    {
        vector<string> hashfile;
        struct stat thestat;
        stat(filename, &thestat);
        size_t filesize = thestat.st_size;
        while (file)
        {
            if (bufferSize > filesize)
            {
                printf("inside if\n");
                bufferSize = filesize;
                unsigned char *buffer = new unsigned char[bufferSize];
                file.read((char *)(buffer), bufferSize);
                // cout << buffer;
                size_t count = file.gcount();
                if (!count)
                    break;
                unsigned char temp[] = "this is it";
                hashfile.push_back(hashFile(temp));
                break;
            }
            else
            {
                printf("else ");
                unsigned char *buffer = new unsigned char[bufferSize];
                file.read((char *)(buffer), bufferSize);
                size_t count = file.gcount();
                if (!count)
                    break;
                hashfile.push_back(hashFile(buffer));
            }
        }

        file.close();
        cout << "hash string: ..";
        for (auto i = hashfile.begin(); i != hashfile.end(); ++i)
        {
            cout << *i << endl
                 << endl;
        }
    }
    else
    {
        printf("cannot open file");
    }
    // cout << buf;
}