
CXX = g++
FLAGS = -W -Wall -pedantic-errors -g -std=c++17 
LIBRARIES = -lpthread

.PHONY: default run

default: run

run:
	${CXX} ${FLAGS} *.cpp ${LIBRARIES} -o program

clean:
	-@rm -rf *.o program core