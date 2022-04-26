SRC = src/starfetch.cpp
GEN_SRC = src/_gen_constellations_list.hpp
GEN = res/res_gen.sh
CC = g++
CFLAGS = -std=c++17 -g
INSTALL_DIR = /usr/local/share
BIN_DIR = /usr/local/bin

all: starfetch

starfetch: ${SRC}
	sh ${GEN} > ${GEN_SRC}
	${CC} ${CFLAGS} ${SRC} -o starfetch

install: starfetch
	rm -rf ${INSTALL_DIR}/starfetch
	mkdir -p ${INSTALL_DIR}/starfetch
	cp -rf ./res/* ${INSTALL_DIR}/starfetch/
	chmod 711 starfetch
	cp -rf starfetch ${INSTALL_DIR}/starfetch/starfetch
	rm -rf ${BIN_DIR}/starfetch
	ln -s ${INSTALL_DIR}/starfetch/starfetch ${BIN_DIR}/starfetch

clean:
	rm -rf starfetch
	rm -rf ${GEN_SRC}

uninstall:
	rm -rf ${INSTALL_DIR}/starfetch
	rm -rf ${BIN_DIR}/starfetch
