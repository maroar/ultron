#!/bin/bash
PROGRAM="./avaliaExpande"
if [ "$1" = "" ] || [ "$2" = "" ] || [ "$3" = "" ]; then
  INPUT_FILE="./tests/assignmentExample"
  POSITIONX="5"
  POSITIONY="1"
else
  INPUT_FILE=$1
  POSITIONX=$2
  POSITIONY=$3
fi

$PROGRAM $INPUT_FILE $POSITIONX $POSITIONY