# starfetch
A command line tool written in C++ that displays constellations.

## Description  
**starfetch** is a tool that prints out a scheme of a given constellation and some information about it: its _quadrant_, its _right ascension_, its _declination_, ita _area_ and its _main stars number_.

## Demo visuals

![ezgif com-gif-maker](https://user-images.githubusercontent.com/61376940/161760086-2033863a-e132-4f28-a3ee-d7bd61c963dc.gif)
<img width="1375" alt="1" src="https://user-images.githubusercontent.com/61376940/161760417-8ba116fc-71a6-4d0c-8219-1b76a4121ace.png">

## Installation
To install **starfetch**, run these commands:

#### MacOS
```
git clone https://github.com/Haruno19/starfetch
cd starfetch
make
sudo make install_mac
```
Install directoy: ``/usr/local/opt/starfetch/``.

#### Others
```
git clone https://github.com/Haruno19/starfetch
cd starfetch
make
sudo make install
```
Install directoy: ``/usr/local/starfetch/``.

## Usage
**starfetch** accepts parameters to tweak its behaviour:
```
starfetch [OPTION] [CONSTELLATION NAME]
    -h      Prints this help message.
    -n      Shows the selected constellation.
    -r      Shows a random constellation.
    -l      Prints the list of all the available constellations.
    
If launched with no arguments, the behaviour is the same as with '-r'.

Examples:   starfetch -r
            starfetch -n orion
            starfetch
```

## Available constellations
```
orion
aries
cancer
cygnus
cassiopeia
libra
virgo
leo
capricorn
taurus
ursa_major
ursa_minor
```
I will add more and more constellations!

## JSON Format
All the constellation data is stored as JSON files in the ``res/constellations/`` directory.  
  
Here's a sample of the JSON format from the **Orion** constellation:
```
{
    "title": "───── ｏｒｉｏｎ ─────",
    "graph":
        {
            "line1": { },
            "line2": { "11": "✦" },
            "line3": { "7": "✦" },
            "line4": { "14": "✦" },
            "line5": { },
            "line6": { "9": "✦", "11": "✦", "13": "✦"},
            "line7": { },
            "line8": { "15": "✦" },
            "line9": { "8": "✦" },
            "line10": { }
        },
    "name": "Orion",
    "quadrant": "NQ1",
    "right ascension": "5h",
    "declination": "+5°",
    "area": "594 sq.deg. (26th)",
    "main stars": "7"
}
```
* ``"title"`` contains the first line of the constellation graph, written with fullwidth Unicode characters.
* ``"graph"`` contains 10 lines keys, describing the constellation graph.
* ``line1 to line10`` contain the X coordinate of the stars on the relative line (e.g. in the 9th line of Orion's graph there are three stars: one at position ``9``, one at poistion ``11`` and one at position ``13``). 
* ``name`` contains the name of the constellation, this time written with regular characters.
* ``quadrant`` contains the quadrant of the constellation.
* ``right ascension`` contains the right ascension of the constellation.
* ``declination`` contains the declination of the constellation.
* ``area`` contains the area of the constellation.
* ``main stars`` contains the number of stars that compose the constellation.
  
## Credits & Dependencies
To work easly with JSON files, starfetch relies on [JSON for Modern C++](https://github.com/nlohmann/json) by [Niels Lohmann](https://github.com/nlohmann).   
Although relying on external libraries, no dependencies are needed to install starfetch, since said library is already included in this repository (``src/include/json.hpp``) via the [single_include](https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp) version provived by the author, in order to make it easier for you, the end user, to enjoy starfetch.
  
---- 
###### All information regarding the constellations are taken from Wikipedia.
