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

void PrintConst(string pathc);  //formats the template file with the requested data and prints out the constellation info   
string RandomConst();   //select a random constellation from the available ones
void PrintList();   //prints out the list of the available constellations
void Error(string err, int type);   //shows an error message
void Help();    //prints out the help message

#ifdef __APPLE__    //selection the right working path based on the OS type
    string path = "/usr/local/opt/starfetch/res/";
#else
    string path = "/usr/local/starfetch/res/";
#endif

int main(int argc, char *argv[])
{
    string pathc = path;    //path to the constellation file
    if(argc == 1)   //if there's no additional arguments
        pathc += RandomConst(); //selects a random constellation
    else
        switch(argv[1][1])  //gets the time of the argument (the 'n' in "-n")
        {
            case 'n':
                if(argc < 3) Error(" ", 0); //if the user requested a '-n' argument but didn't provide a name, an error occours
                pathc += "constellations/"; //updating the path to the constellations folder
                pathc += argv[2];   //adding the name of the requested constellation to the path
                break;
            case 'h':   
                Help();
                break;
            case 'r':
                pathc += RandomConst(); //with the '-r' option, it selects a random constellation
                break;
            case 'l':
                PrintList();
            default:
                Error(argv[1], 1);  //if the reqeusted option isn't recognized, an error occours
        }

    PrintConst(pathc);  //prints the constellation
    return 0;
}

void PrintConst(string pathc)
{
    ifstream c(pathc);  //opens the file containing constellation info
    ifstream f(path+"template");    //opens the output template file
    stringstream strStream;
    string s, l;
    int i=1;

    if(f.is_open()) 
    {
        strStream << f.rdbuf(); //read the template
        s = strStream.str();    //converts it to a tring
        replace(s.begin(), s.end(), '^', '\033');   //replace '^' with the '\e' to print bold/colored text
        f.close();  //closes the template
    }

    if(c.is_open()) 
    {
        while(getline(c,l))
        {
            //replace the placeholders in the template file %i with the lines contained in the selected constellation
            s.replace(s.find("%"+to_string(i)), string("%"+to_string(i)).size(), l);
            i++;
        }
        c.close();
        cout << s << endl;  //prints the output
    }else
        Error("", 2);
}

string RandomConst()
{
    srand(time(NULL));
    
    size_t pos;
    string s;
    
    //SHOULD BE IMPROVED IN THE FUTURE
    //gets every constellation name in the "constellation/" directory, and exits when two randomly generated numbers are equal, resulting in picking a random file
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
    //prints every constellation name from the files name in the "constellations/" directory
    for (const auto & entry : filesystem::directory_iterator(path+"constellations/"))
    {
        pos = entry.path().u8string().find("constellations/"); 
        s = entry.path().u8string().substr(pos+15); //from "/usr/local/opt/starfetch/re/constellations/xxxxxx" to "xxxxxx"
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
