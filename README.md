# starfetch
A command line tool written in C++ that displays constellations.

## Table of contents
* [Description](https://github.com/Haruno19/starfetch#description)
* [Demo visuals](https://github.com/Haruno19/starfetch#demo-visuals)
* [Installation](https://github.com/Haruno19/starfetch#installation)
    * [MacOS](https://github.com/Haruno19/starfetch#macos)
    * [Others](https://github.com/Haruno19/starfetch#others)
* [Usage](https://github.com/Haruno19/starfetch#usage)
* [Available constellations](https://github.com/Haruno19/starfetch#available-constellations)
* [JSON Format](https://github.com/Haruno19/starfetch#json-format)
    * [Contribution guidelines](https://github.com/Haruno19/starfetch#contribution-guidelines)
* [Credits & Dependencies](https://github.com/Haruno19/starfetch#credits--dependencies)
    * [JSON for Modern C++](https://github.com/Haruno19/starfetch#json-for-modern-c)
    * [Contributions](https://github.com/Haruno19/starfetch#contributions)
---

## Description  
**starfetch** is a tool that prints out a scheme of a given constellation and some information about it: its _quadrant_, its _right ascension_, its _declination_, ita _area_ and its _main stars number_.

## Demo visuals

![ezgif com-gif-maker](https://user-images.githubusercontent.com/61376940/161760086-2033863a-e132-4f28-a3ee-d7bd61c963dc.gif)
<img width="1375" alt="1" src="https://user-images.githubusercontent.com/61376940/161760417-8ba116fc-71a6-4d0c-8219-1b76a4121ace.png">

## Installation
To install **starfetch**, run these commands:

### MacOS
```
git clone https://github.com/Haruno19/starfetch
cd starfetch
make
sudo make install_mac
```
Install directoy: ``/usr/local/opt/starfetch/``.

### Others
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
gemini
scorpio
sagittarius
aquarius
ophiuchus
pisces
```
I will add more and more constellations!

## JSON format
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
* ``title`` contains the first line of the constellation graph.
* ``graph`` contains 10 lines keys, describing the constellation graph.
* ``line1`` to ``line10`` contain the X coordinate of the stars on the relative line (e.g. the 6th line of Orion's graph contains three stars: one at position ``9``, one at poistion ``11`` and one at position ``13``). 
* ``name`` contains the name of the constellation, this time written with regular characters.
* ``quadrant`` contains the quadrant of the constellation.
* ``right ascension`` contains the right ascension of the constellation.
* ``declination`` contains the declination of the constellation.
* ``area`` contains the area of the constellation.
* ``main stars`` contains the number of stars that compose the constellation.

### Contribution guidelines
If you want to help this project grow by adding constellation files, here are some guidelines to write correct JSON files:
* The ``"title"`` field should contain the name of the constellation written with [fullwidth Unicode characters](https://en.wikipedia.org/wiki/Halfwidth_and_Fullwidth_Forms_(Unicode_block)).  
Please, make sure to use them. Before and after the name, you have to put the [box-drawing character](https://en.wikipedia.org/wiki/Box-drawing_character) U+2500 as many times as needed to make the line reach the right side of the graph.  
Please, make sure to place the same number of box-drawing characters on both sides, in order to make the name appear at the center.  
Between the constellation name and the box-drawing characters, you should place a whitespace.  
(e.g. ``"───── ｎａｍｅ ─────"``).
* The ``line1`` to ``line10`` field should containd the X coordinates of the stars in each line. 
Please, make sure to center the graph both vertically and horizontally and please, make sure not to leave any star without an X coordinate (e.g. **don't** write this: ``"" : "✦"``).
* The ``"name"`` field should contain the name of the constellation starting with the capital letter.
* The ``"quadrant"`` field should contain the quadrant of the constellation, all in capital letters and without spaces. 
* The ``"right ascension"`` field should contain the right ascension of the constellation.  
Please, make sure to separate each value with a whitespace, and in case a constellation has two right ascension values, separate them with a "to" (e.g. ``"22h 57m 04.5897s to –03h 41m 14.0997s"``).
* The ``declination`` field should contain the declination of the constellation.  
Please, make sure to specify bot - and + symbols for negative and positive values. If there are two declination values, separate them with a "to" (e.g. ``"+77.6923447° to –48.6632690°"``).
* The ``"area"`` field should contain the area of the constellation.  
Please, make sure to include the unit of measurement, written with lowercase letters (e.g. ``"598 sq.deg. (25th)"``).
* The ``"main stars"`` field should contain the number of stars that compose the constellation.
Please, if there's more than a value for this field, make sure to separate them with a comma and a space, and place them in ascending order (e.g. ``"9, 11, 20"``).
  
Your help is really appreciated!
  
## Credits & Dependencies

### JSON for Modern C++
To work easly with JSON files, starfetch relies on [JSON for Modern C++](https://github.com/nlohmann/json) by [Niels Lohmann](https://github.com/nlohmann).   
Although relying on external libraries, no dependencies are needed to install starfetch, since said library is already included in this repository (``src/include/json.hpp``) via the [single_include](https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp) version provided by the author, in order to make it easier for you, the end user, to enjoy starfetch.
  
### Contributions
Credits to John Southern for creating JSON files for the ``gemini``, ``scorpio``, ``sagittarius``, ``aquarius``, ``ophiuchus`` and ``pisces`` constellations!


---- 
###### All data regarding the constellations is taken from Wikipedia.
