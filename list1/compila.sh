#!/bin/bash
BOLD_YELLOW="\e[1;93m"
NO_FORMAT="\e[0m"
COMPILER="g++ -std=c++11 "
SOURCE_CODE_FOLDER="./sourceCode"
# compile the code
# avaliaSucessor.cpp
EXERC1="$SOURCE_CODE_FOLDER/avaliaSucessor.cpp $SOURCE_CODE_FOLDER/PacMaze.cpp $SOURCE_CODE_FOLDER/PacMan.cpp"
echo -e "$BOLD_YELLOW$COMPILER $EXERC1                        -o avaliaSucessor$NO_FORMAT"
$COMPILER $EXERC1 -o avaliaSucessor
# avaliaExpande.cpp
EXERC2="$SOURCE_CODE_FOLDER/avaliaExpande.cpp  $SOURCE_CODE_FOLDER/PacMaze.cpp $SOURCE_CODE_FOLDER/PacMan.cpp"
echo -e "$BOLD_YELLOW$COMPILER $EXERC2                        -o avaliaExpande$NO_FORMAT"
$COMPILER $EXERC2 -o avaliaExpande
# avaliaBFS.cpp
EXERC31="$SOURCE_CODE_FOLDER/avaliaBFS.cpp      $SOURCE_CODE_FOLDER/PacMaze.cpp $SOURCE_CODE_FOLDER/PacMan.cpp $SOURCE_CODE_FOLDER/bfs.cpp"
echo -e "$BOLD_YELLOW$COMPILER $EXERC31   -o avaliaBFS$NO_FORMAT"
$COMPILER $EXERC31 -o avaliaBFS
# avaliaDFS.cpp
EXERC32="$SOURCE_CODE_FOLDER/avaliaDFS.cpp      $SOURCE_CODE_FOLDER/PacMaze.cpp $SOURCE_CODE_FOLDER/PacMan.cpp $SOURCE_CODE_FOLDER/dfs.cpp"
echo -e "$BOLD_YELLOW$COMPILER $EXERC32   -o avaliaDFS$NO_FORMAT"
$COMPILER $EXERC32 -o avaliaDFS
# avaliaAStar.cpp
EXERC33="$SOURCE_CODE_FOLDER/avaliaAStar.cpp    $SOURCE_CODE_FOLDER/PacMaze.cpp $SOURCE_CODE_FOLDER/PacMan.cpp $SOURCE_CODE_FOLDER/astar.cpp"
echo -e "$BOLD_YELLOW$COMPILER $EXERC33 -o avaliaAStar$NO_FORMAT"
$COMPILER $EXERC33 -o avaliaAStar