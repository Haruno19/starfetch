#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <ctime>
#include <filesystem>
#include <random>
//#include <unistd.h> for getpid()
#include "include/json.hpp"

using namespace std;
using json = nlohmann::json;

static inline void PrintConst(string &pathc);  //formats the template file with the requested data and prints out the constellation info   
static string RandomConst();   //select a random constellation from the available ones
static inline void PrintList();   //prints out the list of the available constellations
static void Error(const char *err, int type);   //shows an error message
static void Help();    //prints out the help message

#ifdef _WIN32
  string path = "C:\\starfetch\\";
  string SEP = "\\";
#else
  string path = "/usr/local/share/starfetch/";
  string SEP = "/";
#endif // _WIN32

string REQUESTED_COLOR = "\033[1;36m"; // cyan color

int main(int argc, char *argv[])
{
    string pathc = path;    //path to the constellation file
    if(argc == 1)   //if there's no additional arguments
        pathc += RandomConst(); //selects a random constellation
    else
        switch(argv[1][1])  //gets the time of the argument (the 'n' in "-n")
        {
            case 'n':
            {
                if(argc < 3) Error(" ", 0); //if the user requested a '-n' argument but didn't provide a name, an error occours
                pathc += "constellations" + SEP; //updating the path to the constellations folder
                pathc += argv[2];   //adding the name of the requested constellation to the path
                pathc += ".json";
            }
                break;
            case 'h':   
                Help();
                break;
            case 'r':
                pathc += RandomConst(); //with the '-r' option, it selects a random constellation
                break;
            case 'l':
                PrintList();
                break;
            case 'c':
            {
                if (argc == 2 || argc == 3 || argc == 4)
                {
                    cout << "Available colors are: black, white, cyan, magenta, yellow, red, blue" << endl;
                    return EXIT_SUCCESS;
                }
                else
                {
                    pathc += "constellations" + SEP; //updating the path to the constellations folder
                    pathc += argv[4];   //adding the name of the requested constellation to the path
                    pathc += ".json";
                    if (!strcmp(argv[2], "black"))
                    {
                        REQUESTED_COLOR = "\033[1;30m";
                    }
                    else if (!strcmp(argv[2], "white"))
                    {
                        REQUESTED_COLOR = "\033[1;37m";
                    }
                    else if (!strcmp(argv[2], "cyan"))
                    {
                        REQUESTED_COLOR = "\033[1;36m";
                    }
                    else if (!strcmp(argv[2], "magenta"))
                    {
                        REQUESTED_COLOR = "\033[1;35m";
                    }
                    else if (!strcmp(argv[2], "yellow"))
                    {
                        REQUESTED_COLOR = "\033[1;33m";
                    }
                    else if (!strcmp(argv[2], "red"))
                    {
                        REQUESTED_COLOR = "\033[1;31m";
                    }
                    else if (!strcmp(argv[2], "blue"))
                    {
                        REQUESTED_COLOR = "\033[1;34m";
                    }
                }
            }
                break;
            default:
                Error(argv[1], 1);  //if the reqeusted option isn't recognized, an error occours
                break;
        }

    PrintConst(pathc);  //prints the constellation
    return EXIT_SUCCESS;
}

static inline void PrintConst(string &pathc)
{
    ifstream c(pathc);  //opens the file containing constellation info
    ifstream f(path+"template");    //opens the output template file
    stringstream strStream;
    string s, l;
    json j;

    if(f.is_open()) 
    {
        strStream << f.rdbuf(); //read the template
        s = strStream.str();    //converts it to a string
        replace(s.begin(), s.end(), '^', '\033');   //replace '^' with the '\e' to print bold/colored text
        f.close();  //closes the template
    }

    if(c.is_open()) 
    {
        c >> j;     //parse the selected JSON file
        //fills the template with dats
        s.replace(s.find("%0"), string("%0").size(), j["title"].get<string>());
        s.replace(s.find("%11"), string("%11").size(), j["name"].get<string>());
        s.replace(s.find("%12"), string("%12").size(), j["quadrant"].get<string>());
        s.replace(s.find("%13"), string("%13").size(), j["right ascension"].get<string>());
        s.replace(s.find("%14"), string("%14").size(), j["declination"].get<string>());
        s.replace(s.find("%15"), string("%15").size(), j["area"].get<string>());
        s.replace(s.find("%16"), string("%16").size(), j["main stars"].get<string>());
        
        //renders the constellation's graph from the coordinates specified in the JSON file
        for(int i=1;i<=10;i++)  //for each of the lines (10)
        {
            l="";
            for(int k=1;k<=22;k++)  //for each of the columns of the graph (22)
                //if the JSON file specifies a star at position k
                if(j["graph"]["line"+to_string(i)].find(to_string(k)) != j["graph"]["line"+to_string(i)].end())
                    l+=REQUESTED_COLOR + j["graph"]["line"+to_string(i)][to_string(k)].get<string>() + "\033[0;0m"; //put the star (which is stored into the JSON fine, might change this in the future)
                else
                    l+=" "; //put a space
            
            //insert the line into the template
            s.replace(s.find("%"+to_string(i)), string("%"+to_string(i)).size(), l);
        }

        c.close();
        cout << s << endl;  //prints the output
    }else
        Error("", 2);
}

static string RandomConst()
{
    //srand(static_cast<unsigned int>(time(NULL)) ^ static_cast<unsigned int>(getpid()));
    std::random_device rd;
    std::uniform_int_distribution<int> udist(0, 11);
    size_t pos;
    string s;
    
    //SHOULD BE IMPROVED IN THE FUTURE
    //gets every constellation name in the "constellation/" directory, and exits when two randomly generated numbers are equal, resulting in picking a random file
    for (const auto & entry : filesystem::directory_iterator(path+"constellations" + SEP))
    {
        pos = entry.path().u8string().find("constellations" + SEP);    
        s = entry.path().u8string().substr(pos);
        if(s != "constellations/.DS_Store" && udist(rd) == udist(rd))
            break;
    }

    return s;
}

static inline void PrintList()
{
    string s;

    cout << "✦ \e[1;37mavailable constellations\e[0m: " << endl; 
    //prints every constellation name from the files name in the "constellations/" directory
    for (const auto & entry : filesystem::directory_iterator(path+"constellations" + SEP))
    {
        s = entry.path().u8string().substr(entry.path().u8string().find("constellations" + SEP)+15); //from "/usr/local/opt/starfetch/res/constellations/xxxxxx" to "xxxxxx"
        s = s.substr(0, s.length()-5);
        if(s != ".DS_")    cout << s << endl;
    }  
    exit(EXIT_SUCCESS);
}

static void Error(const char *err, int code)
{
    switch(code)    //each error has a specific code
    {
        case 0: //0 for the missing input
            cout << "Error: you must input a constellation name after -n." << endl << endl;
            break;
        case 1: //1 for the invalid argument
            cout << "Error: '" << err << "' isn't a valid argument." << endl << endl;
            break;
        case 2: //2 for the invalid constellation name
            cout << "Error: the constellation you asked for isn't recognized." << endl << endl;
            break;
    }
    
    Help(); //after any error occours, the help message is shown
}

static void Help()
{
    ifstream f(path + "help_message.txt");
    cout << f.rdbuf();
    f.close();
    exit(EXIT_SUCCESS);
}
