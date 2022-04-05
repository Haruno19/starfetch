# starfetch
A command line tool that displays constellations.

## Description  
**starfetch** is a tool that prints out a scheme of a given constellation and some information about it: its _quadrant_, its _right ascension_, its _declination_, ita _area_ and its _main stars number_.

## Demo visuals

<img width="600" src="https://user-images.githubusercontent.com/61376940/161754280-d007c9f2-157e-49e2-9ef1-0185a771f134.gif">

## How to install
To install **starfetch**, you simply need to clone this repository and run the installation script!

#### MacOS
```
git clone https://github.com/Haruno19/starfetch
cd starfetch
chmod +x ./install_mac.sh
sudo ./install_mac.sh
```
Install directoy: ``/usr/local/opt/starfetch/``.

#### Others
```
git clone https://github.com/Haruno19/starfetch
cd starfetch
chmod +x ./install.sh
sudo ./install.sh
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
