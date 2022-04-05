#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <time.h>

using namespace std;

void PrintConst(string path);
string RandomConst();
void PrintList();
void Error(string err, int type);
void Help();

#ifdef __APPLE__
    string path = "/usr/local/opt/starfetch/";
#else
    string path = "/usr/local/starfetch/";
#endif

int main(int argc, char *argv[])
{
    if(argc == 1)
        path += RandomConst();
    else
        switch(argv[1][1])  //the 'n' in "-n"
        {
            case 'n':
                if(argc < 3) Error(" ", 0);
                path += "constellations/";
                path += argv[2];
                break;
            case 'h':
                Help();
                break;
            case 'r':
                path += RandomConst();
                break;
            case 'l':
                PrintList();
            default:
                Error(argv[1], 1);
        }

    PrintConst(path);
    return 0;
}

void PrintConst(string path)
{
    ifstream f(path);
    stringstream strStream;
    string s;

    if(f.is_open())
    {
        strStream << f.rdbuf();
        s = strStream.str();
        replace(s.begin(), s.end(), '^', '\033');   //replace '^' with the '\e' to print bold/colored text
        std::cout << s << endl;
        f.close();
    }else
        Error("", 2);
}

string RandomConst()
{
    srand(time(NULL));
    ifstream f(path + "/res/c_list.txt");
    string s;
    int max=0;

    while(getline(f,s)) max++;
    f.clear();
    f.seekg(0);
    for(int i=0;i<rand()%max;i++) getline(f,s);
    f.close();

    return "constellations/" + s;
}

void PrintList()
{
    ifstream f(path + "/res/c_list.txt");
    std::cout << "✦ \e[1;37mavailable constellations\e[0m: " << endl << f.rdbuf() << endl;
    f.close();
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
    ifstream f(path + "/res/help_message.txt");
    std::cout << f.rdbuf();
    f.close();
    exit(0);
}
