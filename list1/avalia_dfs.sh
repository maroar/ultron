#!/bin/bash
BOLD_GREEN="\e[1;92m"
NO_FORMAT="\e[0m"
PROGRAM="./avaliaDFS"
INPUT_FILE=$1
ROW=$2
COLUMN=$3
$PROGRAM $INPUT_FILE $ROW $COLUMN

#INPUT_FILE="./tests/assignmentExample"
#ROW="5"
#COLUMN="1"
#echo -e "$BOLD_GREEN$PROGRAM $INPUT_FILE $ROW $COLUMN$NO_FORMAT"
#$PROGRAM $INPUT_FILE $ROW $COLUMN > assignmentExample.dfs.dot 

#INPUT_FILE="./tests/mySimpleExample"
#ROW="1"
#COLUMN="2"
#echo -e "$BOLD_GREEN$PROGRAM $INPUT_FILE $ROW $COLUMN$NO_FORMAT"
#$PROGRAM $INPUT_FILE $ROW $COLUMN > mySimpleExample.dfs.dot

#INPUT_FILE="./tests/myOtherExample"
#ROW="3"
#COLUMN="7"
#echo -e "$BOLD_GREEN$PROGRAM $INPUT_FILE $ROW $COLUMN$NO_FORMAT"
#$PROGRAM $INPUT_FILE $ROW $COLUMN > myOtherExample.dfs.dot