#!/bin/bash
BOLD_YELLOW="\e[1;93m"
NO_FORMAT="\e[0m"
COMPILER="g++ -std=c++11 "
SRC="./sourceCode"
# compile the code
TP="$SRC/scenario.cpp $SRC/action.cpp $SRC/state.cpp $SRC/spot.cpp $SRC/main.cpp $SRC/init.cpp $SRC/searchGraph.cpp $SRC/minMax.cpp $SRC/play.cpp"
echo -e "$BOLD_YELLOW$COMPILER $TP -o tp1$NO_FORMAT"
$COMPILER $TP -o tp1