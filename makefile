SRC = src/starfetch.cpp
CC = g++
CFLAGS = -std=c++17
INSTALL_DIR = /usr/local/share
BIN_DIR = /usr/local/bin

all: starfetch

starfetch: 
	${CC} ${CFLAGS} ${SRC} -o starfetch

install: starfetch
	rm -rf ${INSTALL_DIR}/starfetch
	mkdir -p ${INSTALL_DIR}/starfetch
	cp -rf ./res/* ${INSTALL_DIR}/starfetch/
	chmod 711 starfetch
	cp -rf starfetch ${INSTALL_DIR}/starfetch/starfetch
	rm -rf ${BIN_DIR}/starfetch
	ln -s ${INSTALL_DIR}/starfetch/starfetch ${BIN_DIR}/starfetch
