#include "global.h"

void waitForUpload();
string findPart(string hashkey);

void shareFile(string filename, string filepath)
{
    string fullname = filepath + "/" + filename;
    struct metafile mtorrent = saveTorrentFile((char *)fullname.c_str(), tracker1, tracker2);
    stringstream ss;
    ss << "share\n";
    ss << mtorrent.filename << "\n";
    ss << mtorrent.hash << "\n";
    ss << client.ip << ":" << client.port;
    string buffer1 = ss.str();
    int socketId = createSocketForTracker();
    connectPeers(socketId, tracker1);
    sendRemote(socketId, buffer1);
    string buffer = receiveRemote(socketId);
    log("after closeing connection with tracker");
    string key=filename ;
    // if(!fileAddress[key])
    fileAddress.insert(pair<string,string>(key,fullname)) ;
    replaceExt(filename, "mtorrent");
    // if(mtorrentAddress[key])
    string value = filepath + "/" + filename;
    mtorrentAddress.insert(pair<string,string>(key,value)) ;
    string s=key+"="+mtorrentAddress[key];
    log(s.c_str());
    log("uploading will start now");
    waitForUpload();
}

void waitForUpload()
{
    int socketId = createSocketForClient();
    log("socket created for accepting download request");
    while (1)
    {
        int acc = acceptClient(socketId);
        if (acc > 0)
        {
            string hashkey = receiveRemote(acc);
            log("hashkey recieved");
            string buffer = findPart(hashkey);
            string s="sending "+buffer+" to remote" ;
            log(s.c_str()) ;
            sendRemote(acc, buffer);
            close(acc) ;
        }
    }
}
void printAddresses() ;
string findPart(string hashkey)
{
    printAddresses() ;
    log("insdied find part") ;
    log(hashkey.c_str()) ;
    string filename = hashkey.substr(0, hashkey.length() - 40);
    hashkey=hashkey.substr(filename.length(),40) ;
    cout << filename;
    fstream file;
    string mtorrent = filename;
    // replaceExt(mtorrent, "mtorrent");
    if(strcmp(filename.c_str(),"check.txt")==0)
    log("equal");
    string st="file is "+filename ;
    log(st.c_str());

    string s=mtorrentAddress[filename]+"is mtorrent address";
    log(s.c_str()) ;
    s=fileAddress[filename]+"is file address";
    log(s.c_str()) ;
    file.open(mtorrentAddress[filename], ios::in);
    string hashString = "";
    string line;
    if (file.is_open())
    {
        log("inside if") ;
        getline(file, line) ;
        getline(file, line) ;
        getline(file, line) ;
        getline(file, line) ;        
        while (getline(file, line))
            hashString += line;
        file.close();
    }
    log(hashString.c_str());
    int fileIndex = 0;
    int pos = 0;
    string sub;
    while ((sub = hashString.substr(pos, 40)).length() > 0)
    {
        string msg="matching "+sub+" in hashString" ;
        log(msg.c_str()) ;
        if (strcmp(sub.c_str(), hashkey.c_str()) == 0)
        {
            log("matched") ;
            break;
        }
        pos += 40;
    }
    fileIndex = CHUNK_SIZE * (pos / 40);

    //reading file part
    file.open(fileAddress[filename], ios::in);
    struct stat thestat;
    stat(fileAddress[filename].c_str(), &thestat);
    size_t sz = thestat.st_size;
    sz=sz-fileIndex*CHUNK_SIZE ;
    if (sz > CHUNK_SIZE)
        sz = CHUNK_SIZE;

    char buf[sz+1];
    bzero(buf, (sz+1));
    if (file.is_open())
    {
        file.seekg(fileIndex);
        stringstream ss;
        ss<<"reading "<<sz<<" size of data" ;
        string s=ss.str() ;
        log(s.c_str()) ;
        file.read(buf, sz);
        file.close();
    }
    return string(buf);
}

void printAddresses()
{
    for(auto i=fileAddress.begin(); i!=fileAddress.end() ; ++i)
    {
        string msg=i->first+"="+i->second ;
        log(msg.c_str()) ;
    }
    for(auto i=mtorrentAddress.begin(); i!=mtorrentAddress.end() ; ++i)
    {
        string msg=i->first+"="+i->second ;
        log(msg.c_str()) ;
    }
}