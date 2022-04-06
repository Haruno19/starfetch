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
  
---- 
###### All information regarding the constellations are taken from Wikipedia.
