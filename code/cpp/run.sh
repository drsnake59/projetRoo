#!/bin/bash

g++ -c automata.cpp -I.
g++ -c test.cpp -I.
g++ -o test test.o automata.o

./test solution_19a
