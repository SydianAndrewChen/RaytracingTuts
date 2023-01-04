all:
	mkdir -p bin
	g++ main.cpp -o ./bin/main -fopenmp -O2 -std=c++11