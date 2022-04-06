SRC = src/starfetch.cpp
CC = g++
CFLAGS = -std=c++17
INSTALL_DIR = /usr/local
INSTALL_DIR_MAC = /usr/local/opt
BIN_DIR = /usr/local/bin

all: starfetch

starfetch: 
	${CC} ${CFLAGS} ${SRC} -o starfetch

install_mac: starfetch
	rm -rf ${INSTALL_DIR_MAC}/starfetch
	mkdir -p ${INSTALL_DIR_MAC}/starfetch
	cp -rf ./res ${INSTALL_DIR_MAC}/starfetch/
	chmod 711 starfetch
	cp starfetch ${BIN_DIR}/starfetch

install: starfetch
	rm -rf ${INSTALL_DIR}/starfetch
	mkdir -p ${INSTALL_DIR}/starfetch
	cp -rf ./res ${INSTALL_DIR}/starfetch/
	chmod 711 starfetch
	cp starfetch ${BIN_DIR}/starfetch
