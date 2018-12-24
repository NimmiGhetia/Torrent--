#include "global.h"

vector<string> createHashString(char *filename)
{
    ifstream file;
    file.open(filename, ios::binary | ios::in);
    size_t bufferSize = CHUNK_SIZE;
    vector<string> hashfile;

    if (file.is_open())
    {
        struct stat thestat;
        stat(filename, &thestat);
        size_t filesize = thestat.st_size;
        while (file)
        {
            if (bufferSize > filesize)
            {
                bufferSize = filesize;
                unsigned char *buffer = new unsigned char[bufferSize];
                file.read((char *)(buffer), bufferSize);
                size_t count = file.gcount();
                if (!count)
                    break;
                hashfile.push_back(hashFile(buffer, bufferSize));
                break;
            }
            else
            {
                unsigned char *buffer = new unsigned char[bufferSize];
                file.read((char *)(buffer), bufferSize);
                size_t count = file.gcount();
                if (!count)
                    break;
                hashfile.push_back(hashFile(buffer, bufferSize));
            }
        }
        file.close();
    }
    else
    {
        printf("cannot open file");
    }
    // cout << buf;
    return hashfile;
}

void createFile(struct metafile details);

struct metafile saveTorrentFile(const char *filename, URL url1, URL url2)
{
    struct metafile mtorrent;
    mtorrent.url1 = url1;
    mtorrent.url2 = url2;
    mtorrent.filename = filename;
    struct stat thestat;
    stat(filename, &thestat);
    size_t filesize = thestat.st_size;
    mtorrent.filesize = filesize;
    vector<string> chunkHash = createHashString((char *)filename);
    string hashString = "";
    for (auto i = chunkHash.begin(); i != chunkHash.end(); ++i)
    {
        hashString += (*i);
    }
    mtorrent.hash = hashString;
    createFile(mtorrent);
    string msg = filename;
    msg += "created";
    log(msg.c_str());
    cout << mtorrent.filename << mtorrent.hash;
    return mtorrent;
}
void replaceExt(string &s, const string &newExt)
{

    string::size_type i = s.rfind('.', s.length());

    if (i != string::npos)
    {
        s.replace(i + 1, newExt.length(), newExt);
    }
}

void createFile(struct metafile details)
{
    fstream file;
    string filename = details.filename;
    replaceExt(details.filename, "mtorrent");
    file.open(details.filename, ios::out);
    if (file.is_open())
    {
        file << details.url1.ip;
        file << ":";
        file << details.url1.port;
        file << endl;
        file << details.url2.ip;
        file << ":";
        file << details.url2.port;
        file << endl;
        file << filename << endl;
        file << details.filesize << endl;
        file << details.hash;

        file.close();
    }
}
void printMtorrentFile(struct metafile mtorrent);
struct metafile getTorrentFile(string filename)
{
    cout << "inside getTorrentFile" << endl;
    fstream file;
    struct metafile mtorrent;
    file.open(filename, ios::in);
    if (file.is_open())
    {
        string line;
        int port;
        URL url1, url2;
        stringstream ss;
        getline(file, line);
        url1.ip = getToken(line, ":");
        ss << line;
        ss >> port;
        url1.port = port;
        getline(file, line);
        url2.ip = getToken(line, ":");
        int port2;
        stringstream ss1;
        ss1 << line;
        ss1 >> port;
        url2.port = port;
        mtorrent.url1 = url1;
        mtorrent.url2 = url2;
        getline(file, line);
        mtorrent.filename = line;
        getline(file, line);
        size_t sz;
        stringstream ss2;
        ss2 << line;
        ss2 >> sz;
        mtorrent.filesize = sz;
        mtorrent.hash="" ;
        while (getline(file, line))
        {
            mtorrent.hash += line;
        }
        file.close();
    }
    printMtorrentFile(mtorrent);
    cout<<"file printed. returning..." ;
    return mtorrent;
}

void printMtorrentFile(struct metafile mtorrent)
{
    cout << mtorrent.url1.ip << ":" << mtorrent.url1.port << endl;
    cout << mtorrent.url2.ip << ":" << mtorrent.url2.port << endl;
    cout << mtorrent.filename << endl;
    cout << mtorrent.filesize << endl;
    cout << mtorrent.hash << endl;
}