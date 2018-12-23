#include "global.h"

void printSeederlist();

string getToken(string &file, string delimeter)
{
    string token;
    size_t pos = 0;
    if ((pos = file.find(delimeter)) != string::npos)
    {
        token = file.substr(0, pos);
        file.erase(0, pos + delimeter.length());
        cout << "\nafter changing" << file << "\n";
    }
    return token;
}

vector<URL> getSeederlistFromStorage(string filename)
{
    map<string, vector<URL>> result;
    fstream file;
    file.open(filename, ios::out);
    if (file.is_open())
    {
        string s;
        while (getline(file, s))
        {
            string delimeter = "=";
            string key = getToken(s, "=");
            string urlstring = s;
            string ip = getToken(s, ":");
            stringstream ss;
            ss << getToken(s," ");
            int port;
            ss >> port;
            URL url;
            url.ip = ip;
            url.port = port;
            string path=s;
            result[key].push_back(url);
        }
    }
    seederlist = result;
    return seederlist[filename];
    printSeederlist();
}

vector<URL> getInMemorySeederlist(string filename)
{
    printSeederlist();
    return seederlist[filename];
}

void removeFromSeederlist(string filecontent)
{
    map<string, vector<URL>> result;
    fstream file;
    file.open(seeder_file, ios::in);
    string input, changed_content;
    // vector<URL> list;
    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, input);
            string temp = input;
            string key = getToken(temp, "=");
            if (input.find(filecontent) == string::npos) // check if "John" is not here
            {
                URL url;
                string ip = getToken(temp, ":");
                url.ip = ip;
                int port;
                stringstream ss;
                ss << temp;
                ss >> port;
                url.port = port;
                result[key].push_back(url);
                changed_content += input;
                changed_content += '\n';
            }
            input.clear(); // delete input for new loop
        }
        file.close();
        file.open(seeder_file, ios::out | ios::trunc); // reopen file and clear it's contents
        if (file.is_open())
        {
            file << changed_content; // wite stuff back into the file without john
            file.close();
        }
        else
        {
            cout << "file for rewrite not open\n";
        }
    }
    else
    {
        cout << "file for input not open\n";
    }
    printSeederlist();
    seederlist = result;
    printSeederlist();
}

void printSeederlist()
{
    for (auto it = seederlist.begin(); it != seederlist.end(); ++it)
    {
        cout << it->first;
        for (auto i = (it->second).begin(); i != (it->second).end(); ++i)
            cout << (*i).ip << ":" << (*i).port << endl;
    }
}