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
//#include <unistd.h> for getpid()
#include "include/json.hpp"

using namespace std;
using json = nlohmann::json;
json config;
std::string userLang = "en";
#define CONF config[userLang]

static int run(int argc, char *argv[]);
static void setColor(string color); //sets given color to the REQUESTED_COLOR variable to colorize the output constellation
static inline void PrintConst(string &pathc);  //formats the template file with the requested data and prints out the constellation info
static void PrintList();   //prints out the list of the available constellations
static void Error(const char *err, int type);   //shows an error message
static void Help();    //prints out the help message
static std::string trim(std::string str); // trim excess quotes

#ifdef _WIN32
static string path = "C:\\starfetch\\";
static string SEP = "\\";
#else
static string path = "/usr/local/share/starfetch/";
static string SEP = "/";
#endif // _WIN32
static string directories[2] = {"constellations", "norse-constellations"}; // array that holds all the directory paths. Consider using a multidimensional array to hold the directory name and also the "nickname" to be used for <type> when using "starfetch -n <type> <constellation>"
static string REQUESTED_COLOR = "\033[1;37m"; // white color
static unsigned int useRandomConst = 0U; /* controls whether to use the list with constellations or the input one */
static string configLangs = path + string("langs.json"); // the translated strings for the chosen language that get's setup on startup
ifstream cfg(configLangs); // the langs.json that get's opened and read from

int main(int argc, char *argv[])
{
  try { return run(argc, argv); }
  catch (const json::exception &e) {
    std::cerr << "Error: " << configLangs << " is outdated or broken, copy the new langs.json from the repository (" << e.what() << ")\n";
    return EXIT_FAILURE;
  }
}

int run(int argc, char *argv[])
{
  string requestedLang = "none";
  string pathc = path;    //path to the constellation file
  if (argc >= 2) { requestedLang = string(argv[1]); }
  unsigned int foundRequestedLanguage = 0U;
  if (requestedLang == "en" || requestedLang == "bg" || requestedLang == "it") { userLang = requestedLang; foundRequestedLanguage = 1U; }
  if (!cfg) { cerr << "Error: Could not open " << configLangs << "\n"; return EXIT_FAILURE; }
  if(argc == 1 || argc == 2)   //if there's no additional arguments
  {
    useRandomConst = 1U;
    if (argc == 2 && !strcmp(argv[1], "-l"))
    {
      PrintList();
      return EXIT_SUCCESS;
    }
  }
  else {
    switch(argv[foundRequestedLanguage == 0 ? 1 : 2][1])  //gets the time of the argument (the 'n' in "-n")
    {
      case 'p':
        {
          if(argc < (foundRequestedLanguage == 0 ? 3 : 4)) Error(" ", 0); //if the user requested a '-n' argument but didn't provide a name, an error occurs
          pathc += directories[0] + SEP + argv[foundRequestedLanguage == 0 ? 2 : 3] + ".json"; //updating the path to the constellations folder and adding the name of the requested constallation to the pathc
        }
        break;

        // Refactored -n
      case 'n':
        {
          if(argc < (foundRequestedLanguage == 0 ? 3 : 4)) Error(" ", 0); //if the user requested a '-p' argument but didn't provide a name, an error occurs
          if (static_cast<string>(argv[foundRequestedLanguage == 0 ? 2 : 3]) == "norse" && !(argc < 4)){
          pathc += directories[1] + SEP + argv[foundRequestedLanguage == 0 ? 3 : 4] + ".json"; //updating the path to the constellations folder and adding the name of the requested constallation to the pathc
          } else {
          pathc += directories[0] + SEP + argv[foundRequestedLanguage == 0 ? 2 : 3] + ".json"; // if user didn't specify what constellation tradition, use default constellations
          }
        }
        break;

      case 'h':
        Help();
        return EXIT_SUCCESS;
      case 't':
      {
        useRandomConst = 1U;
      }
        //return EXIT_SUCCESS;
        break;
      case 'r':
      {
        useRandomConst = 1U;
      }
        break;
      case 'c':
        {
          if (argc == (foundRequestedLanguage == 0 ? 2 : 3))
          {
            cout << "Available colors are: black, white, cyan, magenta, yellow, red, blue, green" << endl;
            return EXIT_SUCCESS;
          }
          else if (argc == (foundRequestedLanguage == 0 ? 3 : 4) || argc == (foundRequestedLanguage == 0 ? 4 : 5))
          {
            setColor(static_cast<string>(argv[foundRequestedLanguage == 0 ? 2 : 3]));

            if (argc == (foundRequestedLanguage == 0 ? 4 : 5) && !strcmp(argv[foundRequestedLanguage == 0 ? 3 : 4], "-l"))
            {
              PrintList();
              return EXIT_SUCCESS;
            }

            useRandomConst = 1U;
          }
          else
          {
            pathc += directories[0] + SEP + argv[foundRequestedLanguage == 0 ? 4 : 5] + ".json"; //updating the path to the constellations folder and adding the name of the requested constellation to the pathc
            setColor(static_cast<string>(argv[foundRequestedLanguage == 0 ? 2 : 3]));
          }
        }
        break;
      default:
        Error(argv[1], 1);  //if the reqeusted option isn't recognized, an error occours
        break;
    }
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
  
  ifstream f(path+"template");    //opens the output template file
  stringstream strStream;
  string s, l;
  json j;

  string ConstSet = 
#ifdef _WIN32
  path
#else
 static_cast<string>(getenv("HOME")) + static_cast<string>("/")
#endif // _WIN32
  + static_cast<string>(".fileToParseWithConstellations.txt");

  ifstream file;
  string str;
  vector<string> listWithConst;
  std::random_device rd;
  std::mt19937 gen(rd());

  if (filesystem::exists(ConstSet) && filesystem::is_regular_file(ConstSet))
  {
    file.open(ConstSet, ios::in);
    while (getline(file, str)) {
      listWithConst.emplace_back(str);
    }
    file.close();
  }

  ofstream setFile(ConstSet, ios::out);
  if (!setFile)
  {
    cerr << "Error: Could not open or create file '" << ConstSet << "'\n";
    return;
  }

  if (listWithConst.empty()) {
    for (unsigned int x = 0U; x < 2U; x++) {
      for (const auto &entry : filesystem::directory_iterator(path + directories[x] + SEP))
      {
        listWithConst.emplace_back(entry.path().string());
      }
    }
    shuffle(listWithConst.begin(), listWithConst.end(), gen);
  }
  pathc = (useRandomConst == 1U) ? listWithConst[0] : pathc;
  listWithConst.erase(listWithConst.begin());
  for (const auto &entry : listWithConst)
  {
    setFile << entry << endl;
  }
  setFile.close();

  if(f.is_open())
  {
    strStream << f.rdbuf(); //read the template
    s = strStream.str();    //converts it to a string
    replace(s.begin(), s.end(), '^', '\033');   //replace '^' with the '\e' to print bold/colored text
    f.close();  //closes the template
  }

  ifstream c(pathc);  //opens the file containing constellation info
  cfg >> config;
  cfg.close();
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

    map<string, string> constellationsKeywords = {
      {"Asar Bardagi", trim(CONF["asarBardagi"])}, 
      {"Ulf's Keptr", trim(CONF["ulfsKeptr"])}, 
      {"Kvennavagn", trim(CONF["kvennavagn"])}, 
      {"Karlavagn", trim(CONF["karlavagn"])}, 
      {"Friggerock", trim(CONF["friggerock"])}, 
      {"Andromeda", trim(CONF["andromeda"])}, 
      {"Virgo", trim(CONF["virgo"])}, 
      {"Ursa Minor", trim(CONF["ursaMinor"])}, 
      {"Ursa Major", trim(CONF["ursaMajor"])}, 
      {"Taurus", trim(CONF["taurus"])}, 
      {"Scorpio", trim(CONF["scorpio"])}, 
      {"Sagittarius", trim(CONF["sagittarius"])}, 
      {"Puppis", trim(CONF["puppis"])}, 
      {"Pisces", trim(CONF["pisces"])}, 
      {"Orion", trim(CONF["orion"])}, 
      {"Ophiuchus", trim(CONF["ophiuchus"])}, 
      {"Monoceros", trim(CONF["monoceros"])}, 
      {"Lyra", trim(CONF["lyra"])}, 
      {"Lupus", trim(CONF["lupus"])}, 
      {"Libra", trim(CONF["libra"])}, 
      {"Leo", trim(CONF["leo"])}, 
      {"Gemini", trim(CONF["gemini"])},   
      {"Cygnus", trim(CONF["cygnus"])}, 
      {"Crux", trim(CONF["crux"])}, 
      {"Corona Borealis", trim(CONF["coronaBorealis"])}, 
      {"Circinus", trim(CONF["circinus"])}, 
      {"Centaurus", trim(CONF["centaurus"])}, 
      {"Cassiopeia", trim(CONF["cassiopeia"])}, 
      {"Carina", trim(CONF["carina"])},
      {"Capricorn", trim(CONF["capricorn"])}, 
      {"Canis Minor", trim(CONF["canisMinor"])}, 
      {"Canis Major", trim(CONF["canisMajor"])},
      {"Canes Venatici", trim(CONF["canesVenatici"])}, 
      {"Cancer", trim(CONF["cancer"])}, 
      {"Camelopardalis", trim(CONF["camelopardalis"])},
      {"Caelum", trim(CONF["caelum"])}, 
      {"Auriga", trim(CONF["auriga"])}, 
      {"Boötes", trim(CONF["bootes"])},
      {"Aries", trim(CONF["aries"])}, 
      {"Ara", trim(CONF["ara"])}, 
      {"Aquila", trim(CONF["aquila"])},
      {"Aquarius", trim(CONF["aquarius"])}, 
      {"Apus", trim(CONF["apus"])}, 
      {"Antlia", trim(CONF["antlia"])}
    };
    string nameToMatch = j["name"].get<string>();
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
      s = std::regex_replace(s, std::regex("Quadrant"), trim(CONF["quadrant"]));
      s = std::regex_replace(s, std::regex("Right ascension"), trim(CONF["rightAscension"]));
      s = std::regex_replace(s, std::regex("Declination"), trim(CONF["declination"]));
      s = std::regex_replace(s, std::regex("Area"), trim(CONF["area"]));
      s = std::regex_replace(s, std::regex("Main stars"), trim(CONF["mainStars"]));
      for (const auto &[key, val] : constellationsKeywords)
      {
        if (key == nameToMatch)
        {
          s = std::regex_replace(s, std::regex(key), val);
          break;
        }
      }
    }
    c.close();
    cout << s << endl;  //prints the output
  }else
    Error("", 2);
}

static void PrintList()
{
  string s;

  //cout << REQUESTED_COLOR + "✦  available constellations\033[0;0m:" << endl;
  //prints every constellation name from the files name in the directories array
  for (long unsigned int i = 0; i < sizeof(directories)/sizeof(string); i++){
  cout << "\n" + REQUESTED_COLOR + "✦ available " + directories[i] + "\033[0;0m:" << endl;
    for (const auto & entry : filesystem::directory_iterator(path + directories[i] + SEP))
    {
      s = entry.path().string().substr(entry.path().string().find("constellations" + SEP)+15); //from "/usr/local/opt/starfetch/res/constellations/xxxxxx" to "xxxxxx"
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

// Trim excess quotes
static std::string trim(std::string str) {
  std::string buf;
  for (auto &x : str) {
    if (x == '"') { continue; }
    buf.push_back(x);
  }
  return buf;
}