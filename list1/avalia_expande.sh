#!/bin/bash
BOLD_GREEN="\e[1;92m"
NO_FORMAT="\e[0m"
PROGRAM="./avaliaExpande"

INPUT_FILE="./tests/assignmentExample"
POSITIONX="5"
POSITIONY="1"
INITIAL_COST="3"
echo -e "$BOLD_GREEN$PROGRAM $INPUT_FILE $POSITIONX $POSITIONY $INITIAL_COST$NO_FORMAT"
$PROGRAM $INPUT_FILE $POSITIONX $POSITIONY $INITIAL_COST

INPUT_FILE="./tests/mySimpleExample"
POSITIONX="1"
POSITIONY="2"
INITIAL_COST="6"
echo -e "$BOLD_GREEN$PROGRAM $INPUT_FILE $POSITIONX $POSITIONY $INITIAL_COST$NO_FORMAT"
$PROGRAM $INPUT_FILE $POSITIONX $POSITIONY $INITIAL_COST