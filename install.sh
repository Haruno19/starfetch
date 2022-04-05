#!/bin/sh

INSTALL_DIR='/usr/local/'
BIN_DIR='/usr/local/bin'

rm -rf $INSTALL_DIR/starfetch || return 1

mkdir -p $INSTALL_DIR/starfetch || return 1

cp -rf ./res $INSTALL_DIR/starfetch
g++ ./src/starfetch.cpp -o $INSTALL_DIR/starfetch/starfetch

rm -rf $BIN_DIR/starfetch || return 1
ln -s $INSTALL_DIR/starfetch/starfetch $BIN_DIR/starfetch