CXX = g++ 

CXXFLAGS = -g -std=c++11 -Wall

all: mst

mst: main.o
	${CXX} $^ -o $@
clean:
	/bin/rm -f mst *.o
