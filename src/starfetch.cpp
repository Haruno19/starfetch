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
#include <regex>
#include <list>
#include <map>
#include <fstream>
//#include <unistd.h> for getpid()
#include "include/json.hpp"

using namespace std;
using json = nlohmann::json;

static void setColor(string color); //sets given color to the REQUESTED_COLOR variable to colorize the output constellation
static inline void PrintConst(string &pathc);  //formats the template file with the requested data and prints out the constellation info
//static string RandomConst();   //select a random constellation from the available ones
static string RandomConstRefactor();   //select a random constellation from the available ones
static void PrintList();   //prints out the list of the available constellations
static void Error(const char *err, int type);   //shows an error message
static void Help();    //prints out the help message

#ifdef _WIN32
static string path = "C:\\starfetch\\";
static string SEP = "\\";
#else
static string path = "/usr/local/share/starfetch/";
static string SEP = "/";
#endif // _WIN32
static string directories[2] = {"constellations", "norse-constellations"}; // array that holds all the directory paths. Consider using a multidimensional array to hold the directory name and also the "nickname" to be used for <type> when using "starfetch -n <type> <constellation>"
static string REQUESTED_COLOR = "\033[1;37m"; // white color

int main(int argc, char *argv[])
{
  string pathc = path;    //path to the constellation file
  if(argc == 1)   //if there's no additional arguments
    pathc += RandomConstRefactor(); //selects a random constellation
  else
    switch(argv[1][1])  //gets the time of the argument (the 'n' in "-n")
    {
      case 'p':
        {
          if(argc < 3) Error(" ", 0); //if the user requested a '-n' argument but didn't provide a name, an error occurs
          pathc += directories[0] + SEP + argv[2] + ".json"; //updating the path to the constellations folder and adding the name of the requested constallation to the pathc
        }
        break;

        // Refactored -n
      case 'n':
        {
          if(argc < 3) Error(" ", 0); //if the user requested a '-p' argument but didn't provide a name, an error occurs
          if (static_cast<string>(argv[2]) == "norse" && !(argc < 4)){
          pathc += directories[1] + SEP + argv[3] + ".json"; //updating the path to the constellations folder and adding the name of the requested constallation to the pathc
          } else {
          pathc += directories[0] + SEP + argv[2] + ".json"; // if user didn't specify what constellation tradition, use default constellations
          }
        }
        break;

      case 'h':
        Help();
        return EXIT_SUCCESS;
      case 't':
        pathc += RandomConstRefactor();
        //return EXIT_SUCCESS;
        break;
      case 'r':
        pathc += RandomConstRefactor(); //with the '-r' option, it selects a random constellation
        break;
      case 'l':
        PrintList();
        return EXIT_SUCCESS;
      case 'c':
        {
          if (argc == 2)
          {
            cout << "Available colors are: black, white, cyan, magenta, yellow, red, blue" << endl;
            return EXIT_SUCCESS;
          }
          else if (argc == 3 || argc == 4)
          {
            setColor(static_cast<string>(argv[2]));

            if (argc == 4 && !strcmp(argv[3], "-l"))
            {
              PrintList();
              return EXIT_SUCCESS;
            }

            pathc += RandomConstRefactor();
          }
          else
          {
            pathc += directories[0] + SEP + argv[4] + ".json"; //updating the path to the constellations folder and adding the name of the requested constellation to the pathc
            setColor(static_cast<string>(argv[2]));
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

static void setColor(string color)
{
  static map<string, string> colorKeyword = { {"black", "\033[1;30m"}, {"white", "\033[1;37m"}, {"cyan", "\033[1;36m"}, {"magenta", "\033[1;35m"}, {"yellow", "\033[1;33m"}, {"green", "\033[1;32m"}, {"red", "\033[1;31m"}, {"blue", "\033[1;34m"}};
  for (const auto &[key, val] : colorKeyword) {
    if (color == key) {
      REQUESTED_COLOR = val;
      break;
    }
  }
}

static inline void PrintConst(string &pathc)
{
  ifstream c(pathc);  //opens the file containing constellation info
  ifstream f(path+"template");    //opens the output template file
  stringstream strStream;
  string s, l;
  json j;

  string lastConst = 
#ifdef _WIN32
  path
#else
 static_cast<string>(gentenv("HOME"))
#endif // _WIN32
  + ".starfetch.txt";
  ifstream file;
  unsigned int skipGetline = 0U;

  file.open(lastConst, ios::in);
  if (!file.is_open())
  {
    skipGetline = 1U;
  }
  string str = "";
  if (skipGetline == 0U)
  {
    getline(file, str);
    file.close();
  }
  while (pathc == str)
  {
    pathc = RandomConstRefactor();
  }
  ofstream outToConstFile(lastConst, ios::out);
  if (!outToConstFile)
  {
    cerr << "Error: Could not open file '" << lastConst << "' for writing.\n";
    return;
  }
  outToConstFile << regex_replace(pathc, regex(".starfetch.txt"), "");
  outToConstFile.close();

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
      s = std::regex_replace(s, std::regex("requestedColor"), REQUESTED_COLOR);
    }

    c.close();
    cout << s << endl;  //prints the output
  }else
    Error("", 2);
}


static string RandomConstRefactor()
{

// I'm not a C++ programmer at all, so this is probably super messy, but it works
// refer to the lisp version to get an idea of what to do for the logic
// then reimplement it in C++

  int size_of_directories = sizeof(directories)/sizeof(string);
  int directoryLength = 0;

  std::random_device rd;
  std::mt19937 e(rd());
  std::uniform_int_distribution<int> randdir(0, (size_of_directories - 1));
  auto random_dir = randdir(e);

  size_t pos;
  string s;

  std::list<string> file_list; // list of files to be populated in loop, depending on what the rng decided the directory to be

  for (const auto & entry : filesystem::directory_iterator(path + directories[random_dir] + SEP))
  {
    pos = entry.path().u8string().find(directories[random_dir] + SEP);
    s = entry.path().u8string().substr(pos);
    file_list.push_back(s);
    directoryLength++;
  }

  std::uniform_int_distribution<int> randfile(0, (directoryLength - 1));
  auto random_file = randfile(e);
  std::list<string>::iterator itr = file_list.begin();

  for (int i = 0; i < random_file; i++)
  {
    if (directoryLength == 1 || directoryLength == 0)
    {
      break; // don't iterate, if the directory only has one or 0 items
    } else {
      ++itr;
    }
  }

  return *itr;
}


/*static string RandomConst()
{
  //srand(static_cast<unsigned int>(time(NULL)) ^ static_cast<unsigned int>(getpid()));
  std::random_device rd;
  std::mt19937 e{rd()};
  std::uniform_int_distribution<int> udist(0, 11);
  size_t pos;
  string s;

  //SHOULD BE IMPROVED IN THE FUTURE
  //gets every constellation name in the "constellation/" directory, and exits when two randomly generated numbers are equal, resulting in picking a random file
  for (const auto & entry : filesystem::directory_iterator(path+"constellations" + SEP))
  {
    pos = entry.path().u8string().find("constellations" + SEP);
    s = entry.path().u8string().substr(pos);
    if(s != "constellations/.DS_Store" && udist(e) == udist(e))
      break;
  }
  
  return s;
}*/

static void PrintList()
{
  string s;

  //cout << REQUESTED_COLOR + "✦  available constellations\033[0;0m:" << endl;
  //prints every constellation name from the files name in the directories array
  for (long unsigned int i = 0; i < sizeof(directories)/sizeof(string); i++){
  cout << "\n" + REQUESTED_COLOR + "✦ available " + directories[i] + "\033[0;0m:" << endl;
    for (const auto & entry : filesystem::directory_iterator(path + directories[i] + SEP))
    {
      s = entry.path().u8string().substr(entry.path().u8string().find("constellations" + SEP)+15); //from "/usr/local/opt/starfetch/res/constellations/xxxxxx" to "xxxxxx"
      s = s.substr(0, s.length()-5);
      if(s != ".DS_")    cout << REQUESTED_COLOR + s + "\033[0;0m" << endl;
    }
  }
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