CC = g++
FILE = src/main.cpp
OUTPUT = main
FLAGS = -Wall -Werror -Wextra -pedantic

build:
	${CC} ${FLAGS} ${FILE} -o ${OUTPUT}

buildAndStart:
	${CC} ${FLAGS} ${FILE} -o ${OUTPUT}
