#!/bin/bash
BOLD_GREEN="\e[1;92m"
NO_FORMAT="\e[0m"
PROGRAM="./avaliaAStar"
INPUT_FILE=$1
ROW=$2
COLUMN=$3
$PROGRAM $INPUT_FILE $ROW $COLUMN

#INPUT_FILE="./tests/assignmentExample"
#ROW="5"
#COLUMN="1"
#echo -e "$BOLD_GREEN$PROGRAM $INPUT_FILE $ROW $COLUMN$NO_FORMAT"
#$PROGRAM $INPUT_FILE $ROW $COLUMN > assignmentExample.astar.dot 

#INPUT_FILE="./tests/mySimpleExample"
#ROW="1"
#COLUMN="2"
#echo -e "$BOLD_GREEN$PROGRAM $INPUT_FILE $ROW $COLUMN$NO_FORMAT"
#$PROGRAM $INPUT_FILE $ROW $COLUMN > mySimpleExample.astar.dot

#INPUT_FILE="./tests/myOtherExample"
#ROW="5"
#COLUMN="5"
#echo -e "$BOLD_GREEN$PROGRAM $INPUT_FILE $ROW $COLUMN$NO_FORMAT"
#$PROGRAM $INPUT_FILE $ROW $COLUMN > myOtherExample.astar.dot