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
#include <regex>

#include <QApplication>
#include <QCompleter>
#include <QStringList>
#include <QColor>
#include <QPalette>
#include <QAbstractItemView>
#include <QRandomGenerator>

#include "include/json.hpp"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace std;
using json = nlohmann::json;

static void setColor(string color); //sets given color to the REQUESTED_COLOR variable to colorize the output constellation
static inline void PrintConst(string &pathc);  //formats the template file with the requested data and prints out the constellation info
static string RandomConst();   //select a random constellation from the available ones
static void PrintList();   //prints out the list of the available constellations
static void Error(string &err, int type);   //shows an error message
static void Help();    //prints out the help message

#ifdef _WIN32
  static string path = "C:\\starfetch\\";
  static string SEP = "\\";
#else
  static string path = "/usr/local/share/starfetch/";
  static string SEP = "/";
#endif // _WIN32

static QString oldText = "";
static QStringList wordList = {
    "help", "-r", "-l", "-h", "random", "list", "-n antlia",
    "-n apus", "-n aquarius", "-n ara", "-n aries", "-n bootes", "-n cancer", "-n canes_venatici", "-n cassiopeia",
    "-n corona_borealis", "-n crux", "-n cygnus", "-n gemini", "-n leo", "-n libra", "-n lupus", "-n lyra",
    "-n monoceros", "-n ophiuchus", "-n orion", "-n pisces", "-n sagittarius", "-n scorpio", "-n taurus", "-n ursa_major",
    "-n ursa_minor", "-n virgo"
};
static QCompleter *completer = new QCompleter(wordList, nullptr);

static string REQUESTED_COLOR = "<font color=\"red\">";

Ui::MainWindow *UI;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    UI = ui;

    QPalette p = ui->textEdit->palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    ui->textEdit->setPalette(p);

    ui->textEdit->setText(static_cast<QString>("Type 'help' to see the available command line options"));

    ui->lineEdit->setCompleter(completer);
    completer->popup()->setStyleSheet("background-color:rgb(54, 57, 63); color:white;");

    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_pushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete completer;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    std::string pathc = path;    //path to the constellation file
    std::string userInput = static_cast<std::string>(ui->lineEdit->text().toStdString());
    if (userInput.empty())
    {
        return;
    }

    if(userInput == "-r" || userInput == "random")   //if there's no additional arguments
    {
        pathc += RandomConst(); //selects a random constellation
    }

    else if (userInput == "-h" || userInput == "help")
    {
        Help();
        ui->lineEdit->setText(static_cast<QString>(""));
        return;
    }

    else if (userInput.find("-n ") != std::string::npos)
    {
        pathc += "constellations" + SEP; //updating the path to the constellations folder
        string subStr = std::regex_replace(userInput, std::regex("-n "), "");
        pathc += subStr;   //adding the name of the requested constellation to the path
        pathc += ".json";
    }

    else if (userInput == "-l" || userInput == "list")
    {
        PrintList();
        ui->lineEdit->setText(static_cast<QString>(""));
        return;
    }

    /*else if (userInput.find("-c ") != std::string::npos)
    {
        unsigned short int x = 0U;
        char foundConstellationFlag = 0;
        char color[10] = {'\0'};
        char constellation[20] = {'\0'};
        char *colorPtr = color;
        char *constellationPtr = constellation;
        string subStr = std::regex_replace(userInput, std::regex("-c "), "");
        const char *subStrPtr = subStr.c_str();

        pathc += "constellations" + SEP;

        for (;x < 9U && *subStrPtr; subStrPtr++)
        {
            if (*subStrPtr == ' ')
            {
                subStrPtr++;
                break;
            }
            *colorPtr++ = *subStrPtr;
        }
        *colorPtr = '\0';
        setColor(static_cast<string>(color));

        if (userInput.find("-n ") != std::string::npos)
        {
            subStr = std::regex_replace(subStr, std::regex("-n "), "");
            for (;x < 19U && *subStrPtr; subStrPtr++)
            {
                foundConstellationFlag = 1;
                *constellationPtr++ = *subStrPtr;
            }
            *constellationPtr = '\0';

            pathc += constellation;
            pathc += ".json";
        }
        else if (userInput.find(" -l") != std::string::npos)
        {
            PrintList();
            ui->lineEdit->setText(static_cast<QString>(""));
            return;
        }

        if (foundConstellationFlag == 0)
        {
            pathc += RandomConst();
        }
    }*/
    else
    {
        Error(userInput, 1);  //if the reqeusted option isn't recognized, an error occours
        ui->lineEdit->setText(static_cast<QString>(""));
        return;
    }

    ui->lineEdit->setText(static_cast<QString>(""));
    PrintConst(pathc);  //prints the constellation
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

static void setColor(string color)
{
    if (color == "black")
        REQUESTED_COLOR = "<font color=\"black\">";
    else if (color == "white")
        REQUESTED_COLOR = "<font color=\"white\">";
    else if (color == "cyan")
        REQUESTED_COLOR = "<font color=\"cyan\">";
    else if (color == "magenta")
        REQUESTED_COLOR = "<font color=\"magenta\">";
    else if (color == "yellow")
        REQUESTED_COLOR = "<font color=\"yellow\">";
    else if (color == "red")
        REQUESTED_COLOR = "<font color=\"red\">";
    else if (color == "blue")
        REQUESTED_COLOR = "<font color=\"blue\">";
}

static inline void PrintConst(string &pathc)
{
    ifstream c(pathc);  //opens the file containing constellation info
    ifstream f(path+"template");    //opens the output template file
    stringstream strStream;
    string s, l, subStr;
    json j;

    if(f.is_open())
    {
        strStream << f.rdbuf(); //read the template
        s = strStream.str();    //converts it to a string
        replace(s.begin(), s.end(), '^', ' ');   //replace '^' with the '\e' to print bold/colored text
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
                    l+=j["graph"]["line"+to_string(i)][to_string(k)].get<string>(); //put the star (which is stored into the JSON fine, might change this in the future)
                else
                    for (int z=1;z<4;z++)
                        l+=" "; //put a space
            
            for (int x=1;x<22;x++)
                l+=" ";
            //insert the line into the template
            s.replace(s.find("%"+to_string(i)), string("%"+to_string(i)).size(), l);
        }

        c.close();

        if (s.find("requestedColor") != std::string::npos)
        {
            s = std::regex_replace(s, std::regex("requestedColor"), "");
            s = std::regex_replace(s, std::regex("0m"), "");
            s = std::regex_replace(s, std::regex("\\["), "");
            s = std::regex_replace(s, std::regex("│"), "");
            s = std::regex_replace(s, std::regex("──"), "");
            s = std::regex_replace(s, std::regex("┘"), "");
            s = std::regex_replace(s, std::regex("└"), "");
            s = std::regex_replace(s, std::regex("┌"), "");
            s = std::regex_replace(s, std::regex("┐"), "");
            s = std::regex_replace(s, std::regex("─"), "");
        }

        UI->textEdit->setText(static_cast<QString>(s.c_str()));  //prints the output
    }
}

static string RandomConst()
{
    size_t pos;
    string s;

    //SHOULD BE IMPROVED IN THE FUTURE
    //gets every constellation name in the "constellation/" directory, and exits when two randomly generated numbers are equal, resulting in picking a random file
    for (const auto & entry : filesystem::directory_iterator(path+"constellations" + SEP))
    {
        pos = entry.path().u8string().find("constellations" + SEP);
        s = entry.path().u8string().substr(pos);
        if(s != "constellations/.DS_Store" && QRandomGenerator::global()->bounded(0, 11) == QRandomGenerator::global()->bounded(0, 11))
            break;
    }

    return s;
}

static void PrintList()
{
    string s;
    oldText = "";
    QString outStr = static_cast<string>("✦ Available constellations:\n").c_str();

    UI->textEdit->setText(outStr + oldText + static_cast<QString>("\n"));

    //prints every constellation name from the files name in the "constellations/" directory
    for (const auto & entry : filesystem::directory_iterator(path+"constellations" + SEP))
    {
        s = entry.path().u8string().substr(entry.path().u8string().find("constellations" + SEP)+15); //from "/usr/local/opt/starfetch/res/constellations/xxxxxx" to "xxxxxx"
        s = s.substr(0, s.length()-5);
        if(s != ".DS_")
        {
            oldText += static_cast<QString>(s.c_str()) + static_cast<QString>("\n");
            UI->textEdit->setText(outStr + oldText);
        }
    }
    oldText = "";
}

static void Error(string &err, int code)
{
    switch(code)    //each error has a specific code
    {
        case 0: //0 for the missing input
            UI->textEdit->setText(static_cast<QString>("Error: you must input a constellation name after -n."));
            break;
        case 1: //1 for the invalid argument
            UI->textEdit->setText(static_cast<QString>(static_cast<string>("Error: '" + err + "' isn't a valid argument.").c_str()));
            break;
        case 2: //2 for the invalid constellation name
            UI->textEdit->setText(static_cast<QString>("Error: the constellation you asked for isn't recognized."));
            break;
    }

    Help(); //after any error occours, the help message is shown
}

static void Help()
{
    std::ostringstream ss;
    ifstream f(path + "help_message.txt");
    ss << f.rdbuf();
    string str = ss.str();
    UI->textEdit->setText(static_cast<QString>(str.c_str()));
    f.close();
}
