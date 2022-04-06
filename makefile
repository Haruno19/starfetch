SRC = src/starfetch.cpp
CC = clang++
CFLAGS = -std=c++17
INSTALL_DIR = /usr/local
INSTALL_DIR_MAC = /usr/local/opt
BIN_DIR = /usr/local/bin

all: starfetch

starfetch: 
	${CC} ${CFLAGS} ${SRC} -o starfetch

install_mac: starfetch
	mkdir -p ${INSTALL_DIR_MAC}/starfetch
	cp -rf ./res ${INSTALL_DIR_MAC}/starfetch/
	chmod 711 starfetch
	cp starfetch ${BIN_DIR}/starfetch

install: starfetch
	mkdir -p ${INSTALL_DIR}/starfetch
	cp -rf ./res ${INSTALL_DIR}/starfetch/
	chmod 711 starfetch
	cp starfetch ${BIN_DIR}/starfetch