#include <random>
#include <algorithm>
#include <iostream>

#include "_gen_constellations_list.hpp"

#include "include/json.hpp"
using json = nlohmann::json;

void PrintConst(const std::string &constellation_info);   // formats the template file with the requested data and prints out the constellation info
std::string RandomConst();                   // select a random constellation from the available ones
void PrintList();                            // prints out the list of the available constellations
void Error(const std::string &err, int code);// shows an error message
void Help();                                 // prints out the help message

int main(int argc, char *argv[]) {
    std::string constellation_info;
    if (argc == 1) {             // if there's no additional arguments
        constellation_info = RandomConst();  // selects a random constellation
    } else {
        switch (argv[1][1])// gets the time of the argument (the 'n' in "-n")
        {
            case 'n':
                if (argc < 3) {
                    Error(" ", 0);
                }
                else if(!res_constellations_json_list.count(argv[2])){
                    Error(" ", 2);
                }
                else{
                    constellation_info = res_constellations_json_list[argv[2]];
                }
                break;
            case 'h':
                Help();
                break;
            case 'r':
                constellation_info = RandomConst();// with the '-r' option, it selects a random constellation
                break;
            case 'l':
                PrintList();
            default:
                Error(argv[1], 1);// if the reqeusted option isn't recognized, an error occours
        }
    }

    PrintConst(constellation_info);// prints the constellation
    return 0;
}

void PrintConst(const std::string &constellation_info) {
    json json_data = json::parse(constellation_info);
    std::replace(res_template.begin(), res_template.end(), '^', '\033');// replace '^' with the '\e' to print bold/colored text

    // fills the template with dats
    res_template.replace(res_template.find("%0"), std::string("%0").size(),
                         json_data["title"].get<std::string>());
    res_template.replace(res_template.find("%11"), std::string("%11").size(),
                         json_data["name"].get<std::string>());
    res_template.replace(res_template.find("%12"), std::string("%12").size(),
                         json_data["quadrant"].get<std::string>());
    res_template.replace(res_template.find("%13"), std::string("%13").size(),
                         json_data["right ascension"].get<std::string>());
    res_template.replace(res_template.find("%14"), std::string("%14").size(),
                         json_data["declination"].get<std::string>());
    res_template.replace(res_template.find("%15"), std::string("%15").size(),
                         json_data["area"].get<std::string>());
    res_template.replace(res_template.find("%16"), std::string("%16").size(),
                         json_data["main stars"].get<std::string>());

    // renders the constellation's graph from the coordinates specified in the JSON data
    std::string l_tmp;
    for (int i = 1; i <= 10; i++)// for each of the lines (10)
    {
        l_tmp = "";
        for (int k = 1; k <= 22; k++) {// for each of the columns of the graph (22)
            // if the JSON file specifies a star at position k
            if (json_data["graph"]["line" + std::to_string(i)].find(std::to_string(k)) !=
                json_data["graph"]["line" + std::to_string(i)].end()) {
                l_tmp += json_data["graph"]["line" + std::to_string(i)][std::to_string(k)]
                             .get<std::string>();// put the star (which is stored into the JSON fine, might change this in the future)
            } else {
                l_tmp += " ";// put a space
            }
        }

        // insert the line into the template
        res_template.replace(res_template.find("%" + std::to_string(i)),
                             std::string("%" + std::to_string(i)).size(), l_tmp);
    }
    std::cout << res_template << std::endl;// prints the output
}

std::string RandomConst() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, res_constellations_json_list.size() - 1);

    auto iter = res_constellations_json_list.begin();
    std::advance(iter, dist(mt));

    return iter->second;
}

void PrintList() {
    size_t pos;
    std::string star_name;

    std::cout << "✦ \e[1;37mavailable constellations\e[0m: " << std::endl;
    // prints every constellation name from the list
    for (const auto &[key, _] : res_constellations_json_list){
        std::cout << key << std::endl;
    }
    exit(0);
}

void Error(const std::string &err, int code) {
    switch (code)// each error has a specific code
    {
        case 0:// 0 for the missing input
            std::cout << "Error: you must input a constellation name after -n."
                      << std::endl
                      << std::endl;
            break;
        case 1:// 1 for the invalid argument
            std::cout << "Error: '" << err << "' isn't a valid argument." << std::endl
                      << std::endl;
            break;
        case 2:// 2 for the invalid constellation name
            std::cout << "Error: the constellation you asked for isn't recognized. "
                      << std::endl
                      << std::endl;
    }

    Help();// after any error occours, the help message is shown
}

void Help() {
    std::cout << res_help_message;
    exit(0);
}
