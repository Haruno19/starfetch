#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <filesystem>

using namespace std;

void PrintConst(string path);
string RandomConst();
void PrintList();
void Error(string err, int type);
void Help();

#ifdef __APPLE__
    string path = "/usr/local/opt/starfetch/res/";
#else
    string path = "/usr/local/starfetch/res/";
#endif

int main(int argc, char *argv[])
{
    string pathc = path;    //path to the constellation file
    if(argc == 1)
        pathc += RandomConst();
    else
        switch(argv[1][1])  //the 'n' in "-n"
        {
            case 'n':
                if(argc < 3) Error(" ", 0);
                pathc += "constellations/";
                pathc += argv[2];
                break;
            case 'h':
                Help();
                break;
            case 'r':
                pathc += RandomConst();
                break;
            case 'l':
                PrintList();
            default:
                Error(argv[1], 1);
        }

    PrintConst(pathc);
    return 0;
}

void PrintConst(string pathc)
{
    ifstream c(pathc);
    ifstream f(path+"template");
    stringstream strStream;
    string s, l;
    int i=1;

    if(f.is_open())
    {
        strStream << f.rdbuf();
        s = strStream.str();
        replace(s.begin(), s.end(), '^', '\033');   //replace '^' with the '\e' to print bold/colored text
        f.close();
    }

    if(c.is_open()) //replace the placeholders in the template file %i to the line contained in the selected constellation
    {
        while(getline(c,l))
        {
            s.replace(s.find("%"+to_string(i)), string("%"+to_string(i)).size(), l);
            i++;
        }
        c.close();
        cout << s << endl;
    }else
        Error("", 2);
}

string RandomConst()
{
    srand(time(NULL));
    
    size_t pos;
    string s;
    
    for (const auto & entry : filesystem::directory_iterator(path+"constellations/"))
    {
        pos = entry.path().u8string().find("constellations/");    
        s = entry.path().u8string().substr(pos);
        if(s != "constellations/.DS_Store" && rand()%11 == rand()%11)
            break;
    }

    return s;
}

void PrintList()
{
    size_t pos;
    string s;

    cout << "✦ \e[1;37mavailable constellations\e[0m: " << endl; 
    for (const auto & entry : filesystem::directory_iterator(path+"constellations/"))
    {
        pos = entry.path().u8string().find("constellations/");    
        s = entry.path().u8string().substr(pos+15);
        if(s != ".DS_Store")    cout << s << endl;
    }  
    exit(0);
}

void Error(string err, int type)
{
    switch(type)
    {
        case 0:
            std::cout << "Error: you must input a constellation name after -n or --name." << endl << endl;
            break;
        case 1:
            std::cout << "Error: '" << err << "' isn't a valid argument." << endl << endl;
            break;
        case 2:
            std::cout << "Error: the constellation you asked for isn't recognized." << endl << endl;
    }
    
    Help();
}

void Help()
{
    ifstream f(path + "help_message.txt");
    std::cout << f.rdbuf();
    f.close();
    exit(0);
}
