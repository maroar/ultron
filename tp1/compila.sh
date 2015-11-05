#!/bin/bash
BOLD_YELLOW="\e[1;93m"
NO_FORMAT="\e[0m"
COMPILER="g++ -std=c++11 "
SRC="./sourceCode"
# compile the code
TP="$SRC/scenario.cpp $SRC/piece.cpp $SRC/spot.cpp $SRC/main.cpp $SRC/init.cpp $SRC/placement.cpp $SRC/movement.cpp $SRC/mill.cpp"
echo -e "$BOLD_YELLOW$COMPILER $TP -o tp1$NO_FORMAT"
$COMPILER $TP -o tp1