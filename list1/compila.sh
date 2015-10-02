#!/bin/bash
COMPILER="g++ -std=c++11 "
SOURCE_CODE_FOLDER="./sourceCode"
# compile the code
# avaliaSucessor.cpp
EXERC1="$SOURCE_CODE_FOLDER/avaliaSucessor.cpp $SOURCE_CODE_FOLDER/PacMaze.cpp $SOURCE_CODE_FOLDER/PacMan.cpp"
echo "$COMPILER $EXERC1 -o avaliaSucessor"
$COMPILER $EXERC1 -o avaliaSucessor
# avaliaExpande.cpp
EXERC2="$SOURCE_CODE_FOLDER/avaliaExpande.cpp $SOURCE_CODE_FOLDER/PacMaze.cpp $SOURCE_CODE_FOLDER/PacMan.cpp"
echo "$COMPILER $EXERC2 -o avaliaExpande"
$COMPILER $EXERC2 -o avaliaExpande