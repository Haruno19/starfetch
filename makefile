SRC = src/starfetch.cpp
#CC = g++
CFLAGS = -Wall -Wextra -O2 -ggdb -std=c++20 -pipe -pedantic -Wundef -Wshadow -W -Wwrite-strings -Wcast-align -Wstrict-overflow=5 -Wconversion -Wpointer-arith -Wformat=2 -Wsign-compare -Wendif-labels -Wredundant-decls -Winit-self
INSTALL_DIR = /usr/local/share
BIN_DIR = /usr/local/bin

all: starfetch

starfetch: 
	${CXX} ${CFLAGS} ${SRC} -o starfetch

install:
	rm -rf ${INSTALL_DIR}/starfetch
	mkdir -p ${INSTALL_DIR}/starfetch
	cp -rf ./res/* ${INSTALL_DIR}/starfetch/
	chmod 711 starfetch
	cp -rf starfetch ${INSTALL_DIR}/starfetch/starfetch
	rm -rf ${BIN_DIR}/starfetch
	ln -s ${INSTALL_DIR}/starfetch/starfetch ${BIN_DIR}/starfetch

uninstall:
	rm -rf ${INSTALL_DIR}/starfetch
	unlink ${BIN_DIR}/starfetch

clean:
	rm -rf starfetch

.PHONY: all starfetch install uninstall clean
