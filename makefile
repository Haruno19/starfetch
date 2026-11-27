SRC = src/starfetch.cpp
#CC = g++
CFLAGS = -Wall -Wextra -O2 -ggdb -std=c++20 -pipe -pedantic -Wundef -Wshadow -W -Wwrite-strings -Wcast-align -Wstrict-overflow=5 -Wconversion -Wpointer-arith -Wformat=2 -Wsign-compare -Wendif-labels -Wredundant-decls -Winit-self
PREFIX ?= /usr/local
INSTALL_DIR = ${PREFIX}/share
BIN_DIR = ${PREFIX}/bin
# where starfetch looks for its resources at runtime (must end with a slash)
DATA_DIR ?= ${INSTALL_DIR}/starfetch/

ifneq ($(OS),Windows_NT)
DEFINES = -DSTARFETCH_DATA_DIR='"${DATA_DIR}"'
endif

all: starfetch

starfetch: 
	${CXX} ${CFLAGS} ${DEFINES} ${SRC} -o starfetch

install:
	rm -rf ${INSTALL_DIR}/starfetch
	mkdir -p ${INSTALL_DIR}/starfetch ${BIN_DIR}
	cp -rf ./res/* ${INSTALL_DIR}/starfetch/
	chmod 711 starfetch
	cp -rf starfetch ${INSTALL_DIR}/starfetch/starfetch
	rm -rf ${BIN_DIR}/starfetch
	ln -s ${INSTALL_DIR}/starfetch/starfetch ${BIN_DIR}/starfetch

uninstall:
	rm -rf ${INSTALL_DIR}/starfetch
	unlink ${BIN_DIR}/starfetch

clean:
	rm -rf starfetch starfetch.dSYM

.PHONY: all starfetch install uninstall clean
